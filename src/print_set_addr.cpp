/*
**
**	Network security project - file: print_set_addr.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2018-01-22 20:12:50
**
*/

#include "PacketBuilder.hh"

void            set_mac_addr(const char *src, int *dst)
{
  sscanf(src, "%x:%x:%x:%x:%x:%x",  (unsigned int *) &dst[0],
	 (unsigned int *) &dst[1],
	 (unsigned int *) &dst[2],
	 (unsigned int *) &dst[3],
	 (unsigned int *) &dst[4],
	 (unsigned int *) &dst[5]);
}

void            set_ip_addr(const char *src, int *dst)
{
  sscanf(src, "%d.%d.%d.%d", (int *) &dst[0], (int *) &dst[1], (int *) &dst[2], (int *) &dst[3]);
}

void            print_mac_addr(const char *type, int mac[ETH_ALEN])
{
  printf("%s%x:%x:%x:%x:%x:%x\n", type,
	 mac[0],
	 mac[1],
	 mac[2],
	 mac[3],
	 mac[4],
	 mac[5]);
}

void            print_ip_addr(const char *type, int ip[IP_V4_LEN])
{
  printf("%s%d.%d.%d.%d\n", type, ip[0], ip[1], ip[2], ip[3]);
}
