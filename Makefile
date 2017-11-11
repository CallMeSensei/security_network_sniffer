#
#	Network security project - file: Makefile
#
#	Author: alexandre.jallon@epitech.eu
#	Created on: 2017-11-01 17:36:41
#

SRC =		src/Sniffer.cpp \
			src/FileCapture.cpp \
			src/PacketFactory.cpp \
			src/Packet.cpp \
			src/PacketEthernet.cpp \
			src/PacketIP.cpp \
			src/PacketARP.cpp

AUTO_SAVED =	src/*~ include/*~

OBJ =		$(SRC:.cpp=.o)

NAME =		Sniffer

RM =		rm -f

CC =		g++ -o

CPPFLAGS =	-I./include -std=c++11 -W -Wall -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(NAME) $(OBJ) $(CFLAGS)

clean:
		$(RM) $(OBJ) $(AUTO_SAVED)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
