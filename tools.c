/*
** tools.c for ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Fri May 12 15:31:48 2017 Nicolas Guillon
** Last update Sat May 20 17:54:35 2017 Nicolas Guillon
*/

#include "myftp.h"

void	my_concate(char *tmp, struct core *ftp)
{
  int	len;

  len = strlen(ftp->client.buff);
  tmp[1] = '\0';
  ftp->client.buff = realloc(ftp->client.buff, (strlen(ftp->client.buff) + 2));
  if (ftp->client.buff == NULL)
    printf("ERROR REALLOC\n");
  ftp->client.buff[len] = tmp[0];
  ftp->client.buff[len + 1] = '\0';
}

char	*my_capitalize(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] <= 'z' && str[i] >= 'a')
	str[i] -= 32;
      i++;
    }
  return (str);
}

void	print_format_address(struct core *ftp)
{
  int	i;

  i = 0;
  dprintf(ftp->client_fd, "227 Entering Passive Mode (");
  while (ftp->ip[i])
    {
      if (ftp->ip[i] == '.')
	dprintf(ftp->client_fd, "%c", ',');
      else
	dprintf(ftp->client_fd, "%c", ftp->ip[i]);
      i++;
    }
  dprintf(ftp->client_fd, ",%d,%d).\r\n", ftp->pasv.p1, ftp->pasv.p2);
}

char	*get_com(char *str)
{
  int	i;
  char	*com;

  i = 0;
  while (str[i] && str[i] != ' ')
    i++;
  if ((com = malloc(sizeof(char) * (i + 1))) == NULL)
    return NULL;
  com[i] = 0;
  strncpy(com, str, i);
  return (com);
}

void	unknown_command(char *buff, struct core *ftp)
{
  if (strlen(buff) != 0)
    {
      if (ftp->client.status == LOGGED)
        send_reply("500", "Unknown command.", NULL, ftp);
      else
        send_reply("530", "Please login with USER and PASS.", NULL, ftp);
    }
}
