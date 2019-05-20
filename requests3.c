/*
** requests.c for ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Fri May 12 15:42:11 2017 Nicolas Guillon
** Last update Sun May 21 23:35:15 2017 Nicolas Guillon
*/

#include "myftp.h"

void		do_list(struct core *ftp)
{
  DIR		*dir;
  struct dirent	*ent;

  if ((dir = opendir (ftp->path)) != NULL)
    {
      send_reply("150", "File status okay; about to open data connection.",
		 NULL, ftp);
      dprintf (ftp->pasv.client_fd, "\n");
      while ((ent = readdir (dir)) != NULL)
	{
	  if (ent->d_name[0] != '.')
	    dprintf (ftp->pasv.client_fd, "%s\n", ent->d_name);
	}
      dprintf (ftp->pasv.client_fd, "\r\n");
      send_reply("226", "Closing data connection. Directory send OK.",
		 NULL, ftp);
      closedir(dir);
      close(ftp->pasv.client_fd);
      ftp->pasv.active = false;
    }
  else
    send_reply("550", "Failed to open working directory.", NULL, 0);
}

void	list_command(struct core *ftp)
{
  if (ftp->client.status != LOGGED)
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
  else
    {
      if (ftp->pasv.active != true)
	send_reply("425", "Use PORT or PASV first.", NULL, ftp);
      else
	do_list(ftp);
    }
}

void	pwd_command(char *arg, struct core *ftp)
{
  if (ftp->client.status == LOGGED)
    {
      send_reply("257", ftp->path, NULL, ftp);
    }
  else
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
}

void	dele_command(char *arg, struct core *ftp)
{
  if (ftp->client.status == LOGGED)
    {
      if (remove(arg) == -1)
	send_reply("500", "Illegal command.", NULL, ftp);
      else
	send_reply("250", "Requested file action okay, completed.", NULL, ftp);
    }
  else
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
}

void	cdup_command(struct core *ftp)
{
  if (ftp->client.status == LOGGED)
    {
      send_reply("250", "Directory successfully changed.", NULL, ftp);
      ftp->path = strdup(ftp->root);
    }
  else
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
}
