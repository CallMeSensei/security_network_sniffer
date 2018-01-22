#
#	Network security project - file: Makefile
#
#	Author: alexandre.jallon@epitech.eu
#	Created on: 2017-11-01 17:36:41
#

SRC =		src/PacketBuilder.cpp\
		src/tool.cpp\
		src/help.cpp\
		src/print_set_addr.cpp\
		src/PSender.cpp

SRC2 =		src/Sniffer.cpp 	\
		src/FileCapture.cpp 	\
		src/PacketFactory.cpp 	\
		src/Packet.cpp 		\
		src/PacketEthernet.cpp 	\
		src/PacketIP.cpp 	\
		src/PacketARP.cpp	\
		src/Display.cpp		\
		src/my_lcurses.cpp	\
		src/ScrollTab.cpp	\
		src/ntext.cpp		\
		src/Square.cpp

AUTO_SAVED =	src/*~ include/*~

OBJ =		$(SRC:.cpp=.o)

OBJ2 =		$(SRC2:.cpp=.o)

NAME =		PSender

NAME2 =		Sniffer

RM =		rm -f

CC =		g++ -o

CPPFLAGS =	-I./include -std=c++11 -W -Wall -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(NAME) $(OBJ) $(CFLAGS) -lcurses

$(NAME2):	$(OBJ2)
		$(CC) $(NAME2) $(OBJ2) $(CFLAGS)

clean:
		$(RM) $(OBJ) $(OBJ2) $(AUTO_SAVED)

fclean:		clean
		$(RM) $(NAME) $(NAME2)

re:		fclean all
