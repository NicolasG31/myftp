/*
** main.c for my_ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Tue May  9 15:14:57 2017 Nicolas Guillon
** Last update Sun May 21 18:48:45 2017 Nicolas Guillon
*/

#include "myftp.h"

int     send_reply(const char *code, const char *message,
		   const char *arg, struct core *ftp)
{
  if (code != NULL)
    if (write(ftp->client_fd, code, strlen(code)) == -1)
      {
        printf("Error writing to client fd\n");
        return (1);
      }
  if (message != NULL)
    {
      write(ftp->client_fd, " ", 1);
      if (write(ftp->client_fd, message, strlen(message)) == -1)
        {
          printf("Error writing to client fd\n");
          return (1);
        }
      write(ftp->client_fd, "\r\n", 2);
    }
  else
    write(ftp->client_fd, "\r\n", 2);
  ftp->last_reply.code = code;
  ftp->last_reply.message = message;
  ftp->last_reply.arg = arg;
  return (0);
}

int			my_ftp(struct core *ftp)
{
  if (my_bind(ftp) == 1 || my_listen(ftp) == 1)
    return (1);
  while (42)
    my_ftp_loop(ftp);

  my_end(ftp);
  return (0);
}

void	sighand(int sig)
{
  exit(-1);
}

int			main(int ac, char **av)
{
  struct core		ftp;

  if (ac != 3)
    {
      printf("USAGE: ./server port path\n");
      return (1);
    }
  signal(SIGINT, sighand);
  if (chdir(av[2]) == -1)
    {
      printf("Path '%s' does not exist\n", av[2]);
      return (1);
    }
  if (initialize_struct(&ftp, av) == -1)
    return (1);
  my_ftp(&ftp);
  return (0);
}
