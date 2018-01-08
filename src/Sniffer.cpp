/*
**
**	Network security project - file: sniffer.c
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-01 17:49:17
**
*/
#include <cstdlib>
#include <iostream>
#include <fcntl.h>

#include "Sniffer.hh"
#include "Packet.hh"
#include "Display.h"
#include "PacketFactory.hh"
#include "FileCapture.hh"


int		main(int argc, char **argv)
{
  Display d;
  FileCapture *fc;
  Packet	*packet;
  int  		fd;
  t_sockaddr_in	saddrin;
  int		saddrinlen;
  int		recvlen;
  uint8_t	buffer[BUF_SIZE];

  fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); //ETH_P_ALL = receive all protocol
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
  if (fd < 0)
    {
      perror("Socket");
      return (EXIT_FAILURE);
    }
  d.init_Display();

    if (argc == 2) {
      fc = new FileCapture(std::string(argv[1]), LINKTYPE_ETHERNET);
    } else {
      fc = nullptr;
    }

  while (d.loop())
    {
      saddrinlen = sizeof saddrin;
      recvlen = recvfrom(fd, &buffer, BUF_SIZE, 0, (struct sockaddr*)&saddrin, (socklen_t*)&saddrinlen);
      /*if (recvlen < 0 && recvlen != EWOULDBLOCK && recvlen != EAGAIN)
        {
	  perror("recvlen");
	  d.end_Display();
          return (EXIT_FAILURE);
	}
	else*/ if (recvlen > 0)
	{
	  packet = PacketFactory::create((uint8_t*)&buffer, recvlen);
    if (fc != nullptr)
      *fc << *packet;
	  d.writePacket(packet);
	}
    }
  d.end_Display();
  if (fc != nullptr)
    delete fc;
  if (close(fd) < 0)
    {
      printf("Close failed");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
