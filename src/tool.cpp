/*
**
**	Network security project - file: tool.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-12-20 14:30:57
**
*/

#include "PacketBuilder.hh"

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

void		set_packet_config(t_pconf *pconf, const char *packet)
{
  pconf->packet = create_string(packet);
  pconf->interface = create_string("lo");
  pconf->ip_s = NULL;
  pconf->ip_d = create_string("127.0.0.1");
  pconf->mac_s[0] = -1;
  set_mac_addr("ff:ff:ff:ff:ff:ff", &pconf->mac_d[0]);
  pconf->op = ARPOP_REQUEST;
  pconf->number = 1;
}

options		resolve_opt(const char *opt)
{
  if (strcmp(opt, "-h") == 0) return HELP;
  if (strcmp(opt, "--help") == 0) return HELP;
  if (strcmp(opt, "?") == 0) return HELP_SPECIAL;
  if (strcmp(opt, "-i") == 0) return INTERFACE;
  if (strcmp(opt, "-ips") == 0) return IP_SOURCE;
  if (strcmp(opt, "-ipd") == 0) return IP_DEST;
  if (strcmp(opt, "-macs") == 0) return MAC_SOURCE;
  if (strcmp(opt, "-macd") == 0) return MAC_DEST;
  if (strcmp(opt, "-Ps") == 0) return PORT_SOURCE;
  if (strcmp(opt, "-Pd") == 0) return PORT_DEST;
  if (strcmp(opt, "-op") == 0) return ARP_OP;
  if (strcmp(opt, "-n") == 0) return NUMBER;
  if (strcmp(opt, "-t") == 0) return TIME;
  return OPT_NOT_FOUND;
}

bool		is_number(char *str, const char *error)
{
  int		len = strlen(str);

  for (int i = 0; i < len; i++)
    if (str[i] < '0' || str[i] > '9')
      {
	printf(COLOR_RED "[-] %s\n" COLOR_RESET, error);
	return false;
      }
  return true;
}

int		parse_opt(int argc, char **argv, t_pconf *pconf)
{
  set_packet_config(pconf, argv[1]);
  for (int i = 1; i < argc; i++)
    {
      switch (resolve_opt(argv[i]))
	{
	case HELP:
	  return usage(argv[0]);	  
	case HELP_SPECIAL:
	  if (argc > (i + 1))
	    {
	      if (strcmp(argv[i + 1], "op") == 0) return print_op_help();
	      if (strcmp(argv[i + 1], "PACKET") == 0) return print_packets_help();
	      if (resolve_packet(argv[i + 1]) != PACKET_NOT_FOUND)
		return print_packet_help(resolve_packet(argv[i + 1]));
	    }
	  return usage(argv[0]);
	case INTERFACE:
	  pconf->interface = create_string(argv[i + 1]);
	  break;
	case IP_SOURCE:
	  pconf->ip_s = create_string(argv[i + 1]);
	  break;
	case IP_DEST:
	  pconf->ip_d = create_string(argv[i + 1]);
	  break;
	case MAC_SOURCE:
	  set_mac_addr(argv[i + 1], &pconf->mac_s[0]);
	  break;
	case MAC_DEST:
	  set_mac_addr(argv[i + 1], &pconf->mac_d[0]);
	  break;
	case PORT_SOURCE:
	  if (!is_number(argv[i + 1], "-Ps PORT - PORT as to be a number")) return 1;
	  pconf->port_s = atoi(argv[i + 1]);
	case PORT_DEST:
	  if (!is_number(argv[i + 1], "-Pd PORT - PORT as to be a number")) return 1;
	  pconf->port_d = atoi(argv[i + 1]);
	case ARP_OP:
	  if (!is_number(argv[i + 1], "-op OPERATION - OPERATION as to be a number")) return 1;
	  if (((argv[i + 1][0] < '1' || argv[i + 1][0] > '4')
	       && (argv[i + 1][0] != '8' && argv[i + 1][0] != '9'))
	      || strlen(argv[i + 1]) != 1) return print_op_help();
	  pconf->op = atoi(argv[i + 1]);
	  break;
	case NUMBER:
	  if (!is_number(argv[i + 1], "-n NUMBER - NUMBER as to be a number"))
	    return 1;
	  pconf->number = atoi(argv[i + 1]);
	  break;
	case TIME:
	  if (!is_number(argv[i + 1], "-t TIME - TIME as to be a number"))
	    return 1;
	  pconf->time = atoi(argv[i + 1]);
	  break;
	case OPT_NOT_FOUND:
	  break;
	}
    }
  return 0;
}

packets		resolve_packet(const char *packet)
{
  if (strcmp(packet, "ETH") == 0) return ETH;
  if (strcmp(packet, "IP") == 0) return IP;
  if (strcmp(packet, "TCP") == 0) return TCP;
  if (strcmp(packet, "UDP") == 0) return UDP;
  if (strcmp(packet, "ICMP") == 0) return ICMP;
  if (strcmp(packet, "IGMP") == 0) return IGMP;
  if (strcmp(packet, "ARP") == 0) return ARP;
  return PACKET_NOT_FOUND;
}
