
CC	=	cc
NAME	=	sniffer
RM	=	rm -f

CFLAGS	=	-Wall -Wextra -I./include

SRCS	=	src/example.c

OBJS = $(SRCS:.c=.o)

all:	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
