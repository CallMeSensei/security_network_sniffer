/*
**
**	Network security project - file: main.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-13 21:54:44
**
*/

#include "PacketBuilder.hh"

#define MAC0 0x00
#define MAC1 0x11
#define MAC2 0x22
#define MAC3 0x33
#define MAC4 0x44
#define MAC5 0x55

char*	create_string(const char *src) {
  char *dst;
  unsigned int i = 0;
  
  if ((dst = (char*)malloc((std::strlen(src) + 1) * sizeof(char))) == NULL)
    return NULL;
  for (; i < std::strlen(src); i++)
    dst[i] = src[i];
  dst[i] = '\0';
  return dst;
}

int	main(int ac, char **av) {
  int fd;
  char *int_name = create_string("wlo1\0");
  char *sip = create_string("99.138.147.2\0");
  char *dip = create_string("192.168.1.12\0");
  //char *playload = create_string("HELLO\0");

  if (ac < 2) {
    printf("Usage: packetSender <packet type>\n");
  }

  int smac[6];
  smac[0] = MAC5;
  smac[1] = MAC4;
  smac[2] = MAC3;
  smac[3] = MAC3;
  smac[4] = MAC4;
  smac[5] = MAC5;

  int dmac[6];
  dmac[0] = MAC0;
  dmac[1] = MAC1;
  dmac[2] = MAC2;
  dmac[3] = MAC3;
  dmac[4] = MAC4;
  dmac[5] = MAC5;

  fd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
  if (fd < 0) {
    perror("Socket");
    return 1;
  }
  PacketBuilder *pb = new PacketBuilder(fd, int_name, dmac);
  if (!std::strcmp(av[1], "ETH"))
    {
      pb->Send();
      return 0;
    }
  else if (!std::strcmp(av[1], create_string("IP\0")))
    pb->setIPHeader(sip, dip);
  else if (!std::strcmp(av[1], create_string("ICMP\0")))
    pb->setICMPHeader(sip, dip);
  else if (!std::strcmp(av[1], create_string("UDP\0")))
    pb->setUDPHeader(sip, dip, 4242, 4242);
  else if (!std::strcmp(av[1], create_string("ARP\0")))
    pb->setARPHeader(smac, dmac, sip, dip);
  else {
    printf("Wrong parameter\n");
    return 1;
  }
  pb->Send();
  return 0;
}
