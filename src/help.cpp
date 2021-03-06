/*
**
**	Network security project - file: help.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2018-01-22 20:09:51
**
*/

#include "PacketBuilder.hh"

int             usage(const char *name)
{
  printf("Usage: %s PACKET [ARGS]\n"
	 "\tPACKET\n\t\tThe packet type (ETH, IP, UDP, ICMP, ARP, \"%s ? PACKET\" for more)\n\n"
	 "\t-h, ?, --help\n\t\tDisplay this help message\n\n"
	 "\t?\tFEATURE\n\t\tDisplay a detailed help message about the feature\n\n"
	 "\t-i\tINTERFACE\n\t\tThe interface to send packet on (eth0 by default)\n\n"
	 "\t-ips\tIP_ADDR_SOURCE\n\t\tA spoffed IP address (yours will be taken by default)\n\n"
	 "\t-ipd\tIP_ADDR_DESTINATION\n\t\tThe target ip destination\n\n"
	 "\t-macs\tMAC_ADDR_SOURCE\n\t\tA spoofed mac address(yours will be taken by default)\n\n"
	 "\t-macd\tMAC_ADDR_DESTINATION\n\t\tThe target mac address\n\n"
	 "\t-Ps\tPORT_SOURCE\n\t\tThe source port for UDP\n\n"
	 "\t-Pd\tPORT_DESTINATION\n\t\tThe destination port for UDP\n\n"
	 "\t-op\tOPERATION\n\t\tThe operation for ARP packet (\"%s ? op\" for more)\n\n"
	 "\t-n\tNUMBER\n\t\tThe number of packets to send\n"
	 "\t-t\tTIME\n\t\tThe time between each packet send\n", name, name, name);
  return 1;
}

int             print_op_help()
{
  printf("-op\tOPERATION\n\tOPERATION values: 1, 2, 3, 4, 8, 9:\n\n"
	 "\t1\tARPOP_REQUEST request to resolve address\n"
	 "\t2\tARPOP_REPLY response to previous request\n"
	 "\t3\tARPOP_REVREQUEST request protocol address given hardware\n"
	 "\t4\tARPOP_REVREPLY response giving protocol address\n"
	 "\t8\tARPOP_INVREQUEST request to identify peer\n"
	 "\t9\tARPOP_INVREPLY response identifying peer\n");
  return 1;
}

int		print_packets_help()
{
  printf("PACKET\n\tPACKET values: ETH, IP, ICMP, UDP, ARP:\n\n");
  print_packet_help(ETH);
  printf("\n");
  print_packet_help(IP);
  printf("\n");
  print_packet_help(ICMP);
  printf("\n");
  // print_packet_help(IGMP);
  // printf("\n");
  // print_packet_help(TCP);
  // printf("\n");
  print_packet_help(UDP);
  printf("\n");
  print_packet_help(ARP);
  return 1;
}

int		print_packet_help(packets p)
{
  switch (p)
    {
    case ETH:
      printf("\tETH\tOptions:\n\t\t-i INTERFACE, -macs MAC_ADDR_SOURCE, -macd MAC_ADDR_DESTINATION\n");
      break;
    case IP:
      printf("\tIP\tOptions:\n\t\t-ips IP_ADDR_SOURCE, -ipd IP_ADDR_DESTINATION\n\t\tInherit ETH options\n");
      break;
    case ICMP:
      printf("\tICMP\n\t\tNo options\n\t\tInherit IP options\n");
      break;
    case IGMP:
      printf("\tIGMP\n\t\tNot implemented\n");
      break;
    case TCP:
      printf("\tTCP\n\t\tNot implemented\n");
      break;
    case UDP:
      printf("\tUDP\tOptions:\n\t\t-Ps PORT_SOURCE, -Pd PORT_DESTINATION\n\t\tInherit IP options\n");
      break;
    case ARP:
      printf("\tARP\tOptions:\n\t\t-ips IP_ADDR_SOURCE, -ipd IP_ADDR_DESTINATION -op OPERATION\n"
	     "\t\tInherit ETH options\n");
      break;
    case PACKET_NOT_FOUND:
      printf(COLOR_RED "PACKET not found\n" COLOR_RESET
	     "\tPACKET: ETH, IP, ICMP, UDP, ARP\n");
      break;
    }
  return 1;
}
