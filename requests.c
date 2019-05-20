/*
** requests.c for ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Fri May 12 15:42:11 2017 Nicolas Guillon
** Last update Sun May 21 23:37:33 2017 Nicolas Guillon
*/

#include "myftp.h"


void	do_stor(char *arg, struct core *ftp)
{
  int	file;
  char	tmp[1];
  char	mode[4];
  int	i;

  mode[0] = '0';
  mode[1] = '7';
  mode[2] = '5';
  mode[3] = '5';
  file = open(arg, O_RDWR | O_CREAT);
  if (file < 0)
    send_reply("550", "Failed to create file.", NULL, ftp);
  else
    {
      i = strtol(mode, 0, 8);
      chmod(arg, i);
      dprintf(ftp->client_fd, "150 Uploading file %s.\n", arg);
      while (read(ftp->pasv.client_fd, tmp, 1) > 0)
	write(file, &tmp[0], 1);
      close(file);
      close(ftp->pasv.client_fd);
      ftp->pasv.active = false;
      send_reply("226", "Closing data connection. Transfer complete.",
		 NULL, ftp);
    }
}

void	stor_command(char *arg, struct core *ftp)
{
  if (ftp->client.status != LOGGED)
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
  else
    {
      if (ftp->pasv.active != true)

	send_reply("425", "Use PORT or PASV first.", NULL, ftp);
      else
	do_stor(arg, ftp);
    }
}

void	do_retr(char *arg, struct core *ftp)
{
  char	tmp[1];
  int	file;

  file = open(arg, O_RDONLY);
  if (file >= 0)
    {
      dprintf(ftp->client_fd,
	      "150 Opening ASCII mode data connection for %s.\n"
	      , arg);
      while (read(file, tmp, 1))
	dprintf(ftp->pasv.client_fd, "%c", tmp[0]);
      send_reply("226", "Closing data connection. Transfer complete.",
		 NULL, ftp);
      close(file);
      close(ftp->pasv.client_fd);
      ftp->pasv.active = false;
    }
  else
    send_reply("550", "Failed to open file.", NULL, ftp);
}

void	retr_command(char *arg, struct core *ftp)
{
  if (ftp->client.status != LOGGED)
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
  else
    {
      if (ftp->pasv.active != true)
	send_reply("425", "Use PORT or PASV first.", NULL, ftp);
      else
	do_retr(arg, ftp);
    }
}

