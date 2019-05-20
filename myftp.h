/*
** myftp.h for myftp in /home/nicolas/ftp
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Wed May 10 15:40:35 2017 Nicolas Guillon
** Last update Sat May 20 18:00:47 2017 Nicolas Guillon
*/

#ifndef MY_FTP_H
#define MY_FTP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <stdbool.h>
#include <fcntl.h>

typedef enum		status
  {
    CONNECTED,
    USER,
    LOGGED,
    QUIT
  }			status;

typedef struct		t_last_reply
{
  const char		*code;
  const char		*message;
  const char		*arg;
}			t_last_reply;

typedef struct		t_client
{
  status		status;
  char			*name;
  char			*buff;
}			t_client;

typedef struct		t_pasv
{
  bool			active;
  int			fd;
  int			client_fd;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;
  socklen_t		s_in_size;
  size_t		port;
  int			p1;
  int			p2;
}			t_pasv;

typedef struct		core
{
  char			*ip;
  char			*root;
  char			*path;
  int			fd;
  int			port;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;
  socklen_t		s_in_size;
  int			client_fd;
  char			*client_ip;
  t_last_reply		last_reply;
  t_client		client;
  struct t_pasv		pasv;
}			core;

int		my_bind(struct core *ftp);
int		my_listen(struct core *ftp);
int		my_accept(struct core *ftp);
int		my_end(struct core *ftp);
int		initialize_struct(struct core *ftp, char **av);
int		initialize_pasv(struct core *ftp);
char		**my_str_to_wordtab(char *str);
char		*my_capitalize(char *str);
void		user_command(char *arg, struct core *ftp);
void		pwd_command(char *arg, struct core *ftp);
void		cwd_command(char *arg, struct core *ftp);
void		cdup_command(struct core *ftp);
void		pass_command(char *arg, struct core *ftp);
void		dele_command(char *arg, struct core *ftp);
void		help_command(char *arg, struct core *ftp);
void		pasv_command(char *arg, struct core *ftp);
void		noop_command(struct core *ftp);
void		list_command(struct core *ftp);
void		retr_command(char *arg, struct core *ftp);
void		stor_command(char *arg, struct core *ftp);
void		unknown_command(char *buff, struct core *ftp);
int		send_reply(const char *code, const char *message, const char\
			   *arg, struct core *ftp);
char		*get_com(char *str);
void		print_format_address(struct core *ftp);
void		my_concate(char *tmp, struct core *ftp);
void		handle_request(struct core *ftp, char *buff);
int		found_crlf(struct core *ftp);
int		handle_client(struct core *ftp);
int		my_ftp_loop(struct core *ftp);

#endif
