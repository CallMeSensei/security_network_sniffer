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

#include "Sniffer.hh"
#include "Packet.hh"
#include "Display.h"
#include "PacketFactory.hh"

void		check_proto(t_iphdr *iph)
{
  switch (iph->protocol) //Check the Protocol and do accordingly...
    {
    case 1:  //ICMP
      printf("Protocol: ICMP\n");
      break;
    case 2:  //IGMP
      printf("Protocol: IGMP\n");
      break;
    case 6:  //TCP
      printf("Protocol: TCP\n");
      break;
    case 17: //UDP
      printf("Protocol: UDP\n");
      break;
    case 161: //ARP
      printf("Protocol: ARP\n");
      break;
    default: //Other
      printf("Protocol: ???\n");
      break;
    }
}

int		main()
{
  Packet	*packet;
  int  		fd;
  t_sockaddr_in	saddrin;
  int		saddrinlen;
  int		recvlen;
  uint8_t	buffer[BUF_SIZE];
  t_iphdr	*iph;
  int		i = 0;

  Display	d;

  d.init_Display();
  d.floop();
  d.end_Display();
  
  fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); //ETH_P_ALL = receive all protocol
  if (fd < 0)
    {
      perror("Socket");
      return (EXIT_FAILURE);
    }
  while (1)
    {
      saddrinlen = sizeof saddrin;
      recvlen = recvfrom(fd, &buffer, BUF_SIZE, 0, (struct sockaddr*)&saddrin, (socklen_t*)&saddrinlen);
      if (recvlen < 0)
        {
          printf("recvfrom failed\n");
          return (EXIT_FAILURE);
        }
      packet = PacketFactory::create((uint8_t*)&buffer, recvlen);
      i++;
      iph = (struct iphdr*)(buffer  + sizeof(struct ethhdr));
      check_proto(iph);
      saddrin.sin_addr.s_addr = iph->saddr;

      std::cout << "#########################" << std::endl;
      packet->print();

      delete packet;
    }
  if (close(fd) < 0)
    {
      printf("Close failed");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
