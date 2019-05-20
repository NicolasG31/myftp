/*
** passive.c for my_ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Thu May 18 18:09:25 2017 Nicolas Guillon
** Last update Sat May 20 18:14:34 2017 Nicolas Guillon
*/

#include "myftp.h"

int	fill_struct_pasv(struct core *ftp)
{
  int	len;

  ftp->pasv.port = 1025;
  ftp->pasv.s_in_size = sizeof(ftp->s_in_client);
  ftp->pasv.s_in.sin_family = AF_INET;
  ftp->pasv.s_in.sin_addr.s_addr = INADDR_ANY;
  ftp->pasv.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
  ftp->pasv.s_in.sin_port = htons(ftp->pasv.port);
  if (ftp->pasv.fd == -1)
    {
      printf("Error pasv fd\n");
      return (-1);
    }
  while (bind(ftp->pasv.fd, (const struct sockaddr *)&(ftp->pasv.s_in),\
	      sizeof(ftp->pasv.s_in)) != 0)
    {
      ftp->pasv.port += 1;
      ftp->pasv.s_in.sin_port = htons(ftp->pasv.port);
    }
  len = sizeof(struct sockaddr_in);
  ftp->pasv.p1 = (ftp->pasv.port / 256);
  ftp->pasv.p2 = (ftp->pasv.port % 256);
  getsockname(ftp->client_fd, (struct sockaddr *)&(ftp->pasv.s_in), &len);
  ftp->ip = strdup(inet_ntoa(ftp->pasv.s_in.sin_addr));
  print_format_address(ftp);
}

int	initialize_pasv(struct core *ftp)
{
  fill_struct_pasv(ftp);
  if (listen(ftp->pasv.fd, 1) == -1)
    {
      printf("Error pasv listen\n");
      if (close(ftp->pasv.fd) == -1)
        {
          printf("Error pasv close\n");
          return (1);
        }
      return (1);
    }
  ftp->pasv.client_fd = accept(ftp->pasv.fd, \
			       (struct sockaddr *)&(ftp->pasv.s_in_client),\
			       &(ftp->pasv.s_in_size));
  if (ftp->pasv.client_fd == -1)
    {
      printf("Error accept\n");
      if (close(ftp->pasv.fd) == -1)
        {
          printf("Error close\n");
          return (1);
        }
      return (1);
    }
  ftp->pasv.active = true;
}
