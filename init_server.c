/*
** main.c for my_ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Tue May  9 15:14:57 2017 Nicolas Guillon
** Last update Sat May 20 17:47:46 2017 Nicolas Guillon
*/

#include "myftp.h"

int			my_bind(struct core *ftp)
{
  if (bind(ftp->fd, (const struct sockaddr *)&(ftp->s_in), \
	   sizeof(ftp->s_in)) == -1)
    {
      printf("Error binding\n");
      if (close(ftp->fd) == -1)
	{
	  printf("Error close\n");
	  return (1);
	}
      return (1);
    }
  return (0);
}

int			my_listen(struct core *ftp)
{
  if (listen(ftp->fd, 42) == -1)
    {
      printf("Error listen\n");
      if (close(ftp->fd) == -1)
	{
	  printf("Error close\n");
	  return (1);
	}
      return (1);
    }
  return (0);
}

int			my_accept(struct core *ftp)
{
  ftp->client_fd = accept(ftp->fd, (struct sockaddr *)&(ftp->s_in_client),\
			  &(ftp->s_in_size));
  if (ftp->client_fd == -1)
    {
      printf("Error accept\n");
      if (close(ftp->fd) == -1)
	{
	  printf("Error close\n");
	  return (1);
	}
      return (1);
    }
  return (0);
}

int	my_end(struct core *ftp)
{
  if (close(ftp->fd) == -1)
    {
      printf("Error close");
      return (1);
    }
  if (close(ftp->client_fd) == -1)
    {
      printf("Error close client");
      return (1);
    }
  exit(0);
}

int	initialize_struct(struct core *ftp, char **av)
{
  ftp->pasv.active = false;
  ftp->port = atoi(av[1]);
  ftp->path = av[2];
  ftp->root = av[2];
  if ((ftp->client.buff = malloc(sizeof(char) * 1)) == NULL)
    {
      printf("Error malloc\n");
      return (-1);
    }
  ftp->client.buff[0] = '\0';
  ftp->s_in_size = sizeof(ftp->s_in_client);
  ftp->s_in.sin_family = AF_INET;
  ftp->s_in.sin_port = htons(ftp->port);
  ftp->s_in.sin_addr.s_addr = INADDR_ANY;

  ftp->fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
  if (ftp->fd == -1)
    {
      printf("Error fd\n");
      return (-1);
    }
  return (0);
}
