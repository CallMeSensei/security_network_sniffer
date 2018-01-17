/*
**
**	Network security project - file: main.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-13 21:54:44
**
*/

#include "PacketBuilder.hh"

int		clean(t_pconf *pconf, int fd, int close_fd, int retval)
{
  free(pconf->packet);
  free(pconf->interface);
  free(pconf->ip_s);
  free(pconf->ip_d);
  if (close_fd)
    close(fd);
  return retval;
}

int		main(int argc, char **argv)
{
  int		fd;
  t_pconf	pconf;

  if (argc < 2) {
    usage();
    return 1;
  }
  if (parse_opt(argc, argv, &pconf) == 1)
    return clean(&pconf, 0, FALSE, 1);
  fd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
  if (fd < 0) {
    printf(COLOR_RED "[-] %s\n" COLOR_RESET, strerror(errno));
    printf("\tYou have to be root\n");
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
      printf(COLOR_RED "PACKET_TYPE not found\n" COLOR_RESET
	     "\tPACKET_TYPE: ETH, IP, ICMP, UDP, ARP\n");
      return clean(&pconf, fd, TRUE, 1);
    }
  for (int i = 0; i < pconf.number; i++)
    pb->Send();
  printf(COLOR_GREEN "[+] Packet sent: %d\n" COLOR_RESET "END\n", pconf.number);
  return clean(&pconf, fd, TRUE, 0);
}
