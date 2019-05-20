/*
** requests.c for ftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Fri May 12 15:42:11 2017 Nicolas Guillon
** Last update Sat May 20 18:02:45 2017 Nicolas Guillon
*/

#include "myftp.h"

void	help_command(char *arg, struct core *ftp)
{
  if (ftp->client.status == LOGGED)
    {
      dprintf(ftp->client_fd, "214 The following commands are recognized.\n");
      dprintf(ftp->client_fd, "USER PASS CWD CDUP QUIT DELE PWD PASV PORT ");
      dprintf(ftp->client_fd, "HELP NOOP RETR STOR LIST\n214 Help OK.\r\n");
    }
  else
    send_reply("530", "Please login with USER and PASS.", NULL, ftp);
}
