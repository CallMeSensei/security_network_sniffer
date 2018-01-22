/*
**
**	Network security project - file: main.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-13 21:54:44
**
*/

#include "PacketBuilder.hh"

int		clean(t_pconf *pconf, int fd, bool close_fd, int retval)
{
  free(pconf->packet);
  free(pconf->interface);
  free(pconf->ip_s);
  free(pconf->ip_d);
  if (close_fd)
    close(fd);
  return retval;
}

int		packet_not_found()
{
  printf(COLOR_RED "PACKET_TYPE not found\n" COLOR_RESET
	 "\tPACKET_TYPE: ETH, IP, ICMP, UDP, ARP\n");
  return 1;
}

int		main(int argc, char **argv)
{
  int		fd;
  t_pconf	pconf;

  if (argc < 2) return usage(argv[0]);
  if (parse_opt(argc, argv, &pconf) == 1) return clean(&pconf, 0, false, 1);
  if (resolve_packet_type(argv[1]) == PACKET_NOT_FOUND) return packet_not_found();
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
    case IGMP:
      pb->setIGMPHeader();
      return clean(&pconf, fd, true, 1);
    case TCP:
      pb->setTCPHeader();
      return clean(&pconf, fd, true, 1);
    case UDP:
      pb->setUDPHeader();
      break;
    case ARP:
      pb->setARPHeader();
      break;
    case PACKET_NOT_FOUND:
      packet_not_found();
      return clean(&pconf, fd, true, 1);
    }
  for (int i = 0; i < pconf.number; i++)
    pb->Send();
  printf(COLOR_GREEN "[+] Packet sent: %d\n" COLOR_RESET "END\n", pconf.number);
  return clean(&pconf, fd, true, 0);
}
