##
## Makefile for ftp in /home/nicolas/ftp
## 
## Made by Nicolas Guillon
## Login   <nicolas@epitech.net>
## 
## Started on  Wed May 10 10:31:19 2017 Nicolas Guillon
## Last update Sat May 20 18:00:58 2017 Nicolas Guillon
##

NAME	= server

CC	= gcc

RM	= rm -f

SRCS	= ./server.c \
	  ./init_server.c \
	  ./requests.c \
	  ./requests2.c \
	  ./requests3.c \
	  ./requests4.c \
	  ./loop_serv.c \
	  ./tools.c \
	  ./passive.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I
CFLAGS += -W

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
