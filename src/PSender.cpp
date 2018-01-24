/*
**
**	Network security project - file: main.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-13 21:54:44
**
*/

#include "PacketBuilder.hh"

t_pconf	pconf;
int	fd;
int	count = 0;

int	clean(bool close_fd, int retval)
{
  free(pconf.packet);
  free(pconf.interface);
  free(pconf.ip_s);
  free(pconf.ip_d);
  if (close_fd)
    close(fd);
  return retval;
}

void	make_clean(int)
{
  clean(true, 0);
  printf(COLOR_YELLOW "\b\b[*] User abort signal received\n" COLOR_RESET);
  printf(COLOR_GREEN "[+] Packet sent: %d\n" COLOR_RESET "- END -\n", count);
  exit(0);
}

int	main(int argc, char **argv)
{
  if (argc < 2) return usage(argv[0]);
  if (parse_opt(argc, argv, &pconf) == 1) return clean(false, 1);
  if (resolve_packet(argv[1]) == PACKET_NOT_FOUND)
    return print_packet_help(PACKET_NOT_FOUND);
  fd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
  if (fd < 0) {
    printf(COLOR_RED "[-] %s\n" COLOR_RESET, strerror(errno));
    printf("\tYou have to be root\n");
    return 1;
  }
  signal(SIGINT, make_clean);
  PacketBuilder *pb = new PacketBuilder(fd, pconf);
  switch (resolve_packet(pconf.packet))
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
      return clean(true, 1);
    case TCP:
      pb->setTCPHeader();
      return clean(true, 1);
    case UDP:
      pb->setUDPHeader();
      break;
    case ARP:
      pb->setARPHeader();
      break;
    case PACKET_NOT_FOUND:
      print_packet_help(PACKET_NOT_FOUND);
      return clean(true, 1);
    }
  for (; count < pconf.number; count++)
    {
      pb->Send();
      if (pconf.time > 0) sleep(pconf.time);
    }
  printf(COLOR_GREEN "[+] Packet sent: %d\n" COLOR_RESET "- END -\n", count);
  return clean(true, 0);
}
