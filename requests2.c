/*
** requests.c for ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Fri May 12 15:42:11 2017 Nicolas Guillon
** Last update Sat May 20 17:34:24 2017 Nicolas Guillon
*/

#include "myftp.h"

void	cwd_command(char *arg, struct core *ftp)
{
  if (ftp->client.status == LOGGED)
    {
      if (chdir(arg) == -1)
	send_reply("550", "Failed to change directory.", NULL, ftp);
      else
	{
	  send_reply("250", "Directory successfully changed.", NULL, ftp);
	  ftp->path = strdup(arg);
	}
    }
  else
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
}

void	user_command(char *arg, struct core *ftp)
{
  if (ftp->client.status == LOGGED)
    send_reply("530", "Can't change from guest user.", NULL, ftp);
  else
    {
      send_reply("331", "User name okay, need password.", NULL, ftp);
      ftp->client.status = USER;
      ftp->client.name = malloc(sizeof(char) * (strlen(arg) + 1));
      if (ftp->client.name == NULL)
	return;
      strcpy(ftp->client.name, arg);
    }
}

void	pasv_command(char *arg, struct core *ftp)
{
  initialize_pasv(ftp);
  return;
}

void	pass_command(char *arg, struct core *ftp)
{
  if (ftp->client.status == CONNECTED)
    send_reply("503", "Login with USER first.", NULL, ftp);
  else
    {
      if (strncmp(my_capitalize(ftp->client.name), "ANONYMOUS", 9))
	{
	  send_reply("530", "Login incorrect.", NULL, ftp);
	  ftp->client.status = CONNECTED;
	}
      else
	{
	  send_reply("230", "User logged in, proceed.", NULL, ftp);
	  ftp->client.status = LOGGED;
	}
    }
}

void	noop_command(struct core *ftp)
{
  if (ftp->client.status != LOGGED)
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
  else
    send_reply("200", "NOOP ok.", NULL, ftp);
}
