/*
**
**	Network security project - file: tool.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-12-20 14:30:57
**
*/

#include "PacketBuilder.hh"

void		usage()
{
  printf("Usage: packetSender PACKET_TYPE [ARGS]\n"
	 "\tPACKET_TYPE\tThe packet type (ETH, IP, UDP, ICMP, ARP)\n"
	 "\t-h, ?, --help\tDisplay this help message\n"
	 "\t-i\t\tThe interface to send packet on (eth0 by default)\n"
	 "\t-ips\t\tA spoffed IP address (yours will be taken by default)\n"
	 "\t-ipd\t\tThe target ip destination\n"
	 "\t-macs\t\tA spoofed mac address(yours will be taken by default)\n"
	 "\t-macd\t\tThe target mac address\n"
	 "\t-Ps\t\tThe source port for UDP\n"
	 "\t-Pd\t\tThe destination port for UDP\n"
	 "\t-n\t\tThe number of packets to send\n");
}

char*           create_string(const char *src) {
  char          *dst;
  unsigned int  i = 0;

  if ((dst = (char*)malloc((std::strlen(src) + 1) * sizeof(char))) == NULL)
    return NULL;
  for (; i < std::strlen(src); i++)
    dst[i] = src[i];
  dst[i] = '\0';
  return dst;
}

void		set_mac_addr(const char *src, int *dst)
{
  sscanf(src, "%x:%x:%x:%x:%x:%x",  (unsigned int *) &dst[0],
	 (unsigned int *) &dst[1],
	 (unsigned int *) &dst[2],
	 (unsigned int *) &dst[3],
	 (unsigned int *) &dst[4],
	 (unsigned int *) &dst[5]);
}

void		set_ip_addr(const char *src, int *dst)
{
  sscanf(src, "%d.%d.%d.%d", (int *) &dst[0], (int *) &dst[1], (int *) &dst[2], (int *) &dst[3]);
}

void		print_mac_addr(const char *type, int mac[ETH_ALEN])
{
  printf("%s%x:%x:%x:%x:%x:%x\n", type,
	 mac[0],
	 mac[1],
	 mac[2],
	 mac[3],
	 mac[4],
	 mac[5]);
}

void		print_ip_addr(const char *type, int ip[IP_V4_LEN])
{
  printf("%s%d.%d.%d.%d\n", type, ip[0], ip[1], ip[2], ip[3]);
}

void		set_packet_config(t_pconf *pconf, const char *packet)
{
  pconf->packet = create_string(packet);
  pconf->interface = create_string("lo");
  pconf->ip_s = create_string("127.0.0.1");
  pconf->ip_d = create_string("127.0.0.1");
  pconf->number = 1;
  set_mac_addr("00:11:22:33:44:55", &pconf->mac_d[0]);
}

options		resolve_opt(const char *opt)
{
  if (strcmp(opt, "-h") == 0) return HELP;
  if (strcmp(opt, "--help") == 0) return HELP;
  if (strcmp(opt, "?") == 0) return HELP;
  if (strcmp(opt, "-i") == 0) return INTERFACE;
  if (strcmp(opt, "-ips") == 0) return IP_SOURCE;
  if (strcmp(opt, "-ipd") == 0) return IP_DEST;
  if (strcmp(opt, "-macs") == 0) return MAC_SOURCE;
  if (strcmp(opt, "-macd") == 0) return MAC_DEST;
  if (strcmp(opt, "-Ps") == 0) return PORT_SOURCE;
  if (strcmp(opt, "-Pd") == 0) return PORT_DEST;
  if (strcmp(opt, "-n") == 0) return NUMBER;
  return OPT_NOT_FOUND;
}

int		is_number(char *str, const char *error)
{
  int		len = strlen(str);

  for (int i = 0; i < len; i++)
    if (str[i] < '0' || str[i] > '9')
      {
	printf("%s\n", error);
	return FALSE;
      }
  return TRUE;
}

int		parse_opt(int argc, char **argv, t_pconf *pconf)
{
  set_packet_config(pconf, argv[1]);
  for (int i = 2; i < argc; i++)
    {
      switch (resolve_opt(argv[i]))
	{
	case HELP:
	  usage();
	  return 1;
	  break;
	case INTERFACE:
	  pconf->interface = create_string(argv[i + 1]);
	  break;
	case IP_SOURCE:
	  pconf->ip_s = create_string(argv[i + 1]);
	  pconf->ip_s_set = true;
	  break;
	case IP_DEST:
	  pconf->ip_d = create_string(argv[i + 1]);
	  break;
	case MAC_SOURCE:
	  set_mac_addr(argv[i + 1], &pconf->mac_s[0]);
	  pconf->mac_s_set = true;
	  break;
	case MAC_DEST:
	  set_mac_addr(argv[i + 1], &pconf->mac_d[0]);
	  break;
	case PORT_SOURCE:
	  if (!is_number(argv[i + 1], "-Ps PORT - PORT as to be a number"))
	    return 1;
	  pconf->port_s = atoi(argv[i + 1]);
	case PORT_DEST:
	  if (!is_number(argv[i + 1], "-Pd PORT - PORT as to be a number"))
	    return 1;
	  pconf->port_d = atoi(argv[i + 1]);
	case NUMBER:
	  if (!is_number(argv[i + 1], "-n NUMBER - NUMBER is the number of packet to send as to be a number"))
	    return 1;
	  pconf->number = atoi(argv[i + 1]);
	case OPT_NOT_FOUND:
	  break;
	}
    }
  return 0;
}

packets		resolve_packet_type(const char *packet)
{
  if (strcmp(packet, "ETH") == 0) return ETH;
  if (strcmp(packet, "IP") == 0) return IP;
  //if (strcmp(packet, "TCP") == 0) return TCP;
  if (strcmp(packet, "UDP") == 0) return UDP;
  if (strcmp(packet, "ICMP") == 0) return ICMP;
  //if (strcmp(packet, "IGMP") == 0) return IGMP;
  if (strcmp(packet, "ARP") == 0) return ARP;
  return PACKET_NOT_FOUND;
}
