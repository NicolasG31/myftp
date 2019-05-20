/*
** main.c for my_ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Tue May  9 15:14:57 2017 Nicolas Guillon
** Last update Sun May 21 18:46:14 2017 Nicolas Guillon
*/

#include "myftp.h"

void	handle_request2(struct core *ftp, char *buff, char *com, char *arg)
{
  if (!strcmp(com, "HELP"))
    help_command(arg, ftp);
  else if (!strcmp(com, "DELE"))
    dele_command(arg, ftp);
  else if (!strcmp(com, "LIST"))
    list_command(ftp);
  else if (!strcmp(com, "RETR"))
    retr_command(arg, ftp);
  else if (!strcmp(com, "STOR"))
    stor_command(arg, ftp);
  else if (!strcmp(com, "PASV"))
    pasv_command(arg, ftp);
  else
    unknown_command(buff, ftp);
}

void	handle_request(struct core *ftp, char *buff)
{
  char	*com;
  char	*arg;

  com = my_capitalize(get_com(buff));
  arg = &buff[strlen(com) + 1];
  if (!strcmp(com, "QUIT"))
    send_reply("221", "Service closing control connection.", NULL, ftp);
  else if (!strcmp(com, "NOOP"))
    noop_command(ftp);
  else if (!strcmp(com, "CDUP"))
    cdup_command(ftp);
  else if (!strcmp(com, "USER"))
    user_command(arg, ftp);
  else if (!strcmp(com, "PASS"))
    pass_command(arg, ftp);
  else if (!strcmp(com, "PWD"))
    pwd_command(arg, ftp);
  else if (!strcmp(com, "CWD"))
    cwd_command(arg, ftp);
  else
    handle_request2(ftp, buff, com, arg);
}

int	found_crlf(struct core *ftp)
{
  int	len;
  int	i;
  char	*str;

  len = strlen(ftp->client.buff);
  i = 0;
  while (ftp->client.buff[i])
    {
      if (ftp->client.buff[i] == '\n' && ftp->client.buff[i - 1] == '\r')
	{
	  str = malloc(sizeof(char) * (i));
	  strncpy(str, ftp->client.buff, i - 1);
	  str[i - 1] = '\0';
	  strcpy(ftp->client.buff, str);
	  return (i);
	}
      i++;
    }
  return (0);
}

int	handle_client(struct core *ftp)
{
  char	tmp[2];

  tmp[0] = '\0';
  send_reply("220", "Service ready for new user.", NULL, ftp);
  ftp->client.status = CONNECTED;
  while (ftp->last_reply.code != "221")
    {
      if (found_crlf(ftp) != 0)
	{
	  handle_request(ftp, ftp->client.buff);
	  ftp->client.buff = realloc(ftp->client.buff, 2);
	  ftp->client.buff[0] = '\0';
	}
      if (ftp->last_reply.code != "221")
	{
	  read(ftp->client_fd, tmp, 1);
	  my_concate(tmp, ftp);
	}
    }
  close(ftp->client_fd);
  return 0;
}

int			my_ftp_loop(struct core *ftp)
{
  pid_t			pid;

  my_accept(ftp);
  pid = fork();
  if (pid < 0)
    {
      printf("error fork\n");
      exit(-1);
    }
  if (pid == 0)
    {
      ftp->client_ip = inet_ntoa(ftp->s_in_client.sin_addr);
      handle_client(ftp);
    }
  else
    close(ftp->client_fd);
}
