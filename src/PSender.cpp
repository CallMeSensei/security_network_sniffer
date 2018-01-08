/*
**
**	Network security project - file: main.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-13 21:54:44
**
*/

#include "PacketBuilder.hh"

int		main(int argc, char **argv)
{
  int		fd;
  t_pconf	pconf;

  if (argc < 2) {
    usage();
    return 1;
  }
  if (parse_opt(argc, argv, &pconf) == 1)
    return 0;
  fd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
  if (fd < 0) {
    perror("Socket");
    return 1;
  }
  PacketBuilder *pb = new PacketBuilder(fd, pconf);
  switch (resolve_packet_type(pconf.packet))
    {
    case ETH:
      pb->setEthernetHeader();
      break;
    case IP:
      pb->setIPHeader();
      break;
    case ICMP:
      pb->setICMPHeader();
      break;
    case UDP:
      pb->setUDPHeader();
      break;
    case ARP:
      pb->setARPHeader();
      break;
    case PACKET_NOT_FOUND:
      printf("PACKET_TYPE not found\n"
	     "\tPACKET_TYPE: ETH, IP, ICMP, UDP, ARP\n");
      close(fd);
      return 1;
    }
  pb->Send();
  printf("Packet sent\nEND\n");
  free(pconf.packet);
  free(pconf.interface);
  free(pconf.ip_s);
  free(pconf.ip_d);
  close(fd);
  return 0;
}
