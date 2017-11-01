#
#	Network security project - file: Makefile
#
#	Author: alexandre.jallon@epitech.eu
#	Created on: 2017-11-01 17:36:41
#

SRC =		src/sniffer.c

AUTO_SAVED =	src/*~ include/*~

OBJ =		$(SRC:.c=.o)

NAME =		sniffer

RM =		rm -f

CC =		gcc -o

CFLAGS =	-W -Wall -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(NAME) $(OBJ) $(CFLAGS)

clean:
		$(RM) $(OBJ) $(AUTO_SAVED)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
