/*
**
**	Network security project - file: PSender.hh
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-12-20 14:37:58
**
*/

#ifndef PSENDER_HH_
#define PSENDER_HH_

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>

#define DEFAULT_PORT 4242
#define IP_V4_LEN 4
#define TRUE 1
#define FALSE 0

enum		e_options
  {
    OPT_NOT_FOUND,
    HELP,
    INTERFACE,
    IP_SOURCE,
    IP_DEST,
    MAC_SOURCE,
    MAC_DEST,
    PORT_SOURCE,
    PORT_DEST,
    NUMBER
  } typedef	options;

enum		e_packets
  {
    PACKET_NOT_FOUND,
    ETH,
    IP,
    UDP,
    ICMP,
    ARP
  } typedef	packets;

struct		s_packet_config
{
  char		*packet;
  char		*interface;
  char		*ip_s;
  char		*ip_d;
  int		port_s = DEFAULT_PORT;
  int		port_d = DEFAULT_PORT;
  int		mac_s[ETH_ALEN];
  int		mac_d[ETH_ALEN];
  bool		mac_s_set = false;
  bool		ip_s_set = false;
  int		number;
} typedef	t_pconf;

/* tool.cpp */
void		usage();
char*		create_string(const char *src);
void		set_mac_addr(const char *src, int *dst);
void		set_ip_addr(const char *src, int *dst);
void		print_mac_addr(const char *type, int mac[ETH_ALEN]);
void		print_ip_addr(const char *type, int ip[IP_V4_LEN]);
void            set_packet_config(t_pconf *pconf, const char *packet);
options		resolve_opt(const char *opt);
int		is_number(char *str, const char *error);
int		parse_opt(int argc, char **argv, t_pconf *pconf);
packets		resolve_packet_type(const char *packet);

#endif /* PSENDER_HH_ */
