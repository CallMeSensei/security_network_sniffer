/*
**
**	Network security project - file: PacketBuilder.hh
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-11 21:05:54
**
*/

#ifndef PACKET_BUILDER_HH_
#define PACKET_BUILDER_HH_

#include "PSender.hh"

#include <cstring>

#define BUF_SIZE 2048
#define DEFAULT_TTL 64
#define IP_V4_LEN 4

#define ICMP_ECHOREPLY		0	/* Echo Reply*/
#define ICMP_DEST_UNREACH	3	/* Destination Unreachable*/
#define ICMP_SOURCE_QUENCH	4	/* Source Quench*/
#define ICMP_REDIRECT		5	/* Redirect (change route)*/
#define ICMP_ECHO		8	/* Echo Request*/
#define ICMP_TIME_EXCEEDED	11	/* Time Exceeded*/
#define ICMP_PARAMETERPROB	12	/* Parameter Problem*/
#define ICMP_TIMESTAMP		13	/* Timestamp Request*/
#define ICMP_TIMESTAMPREPLY	14	/* Timestamp Reply*/
#define ICMP_INFO_REQUEST	15	/* Information Request*/
#define ICMP_INFO_REPLY		16	/* Information Reply*/
#define ICMP_ADDRESS		17	/* Address Mask Request*/
#define ICMP_ADDRESSREPLY	18	/* Address Mask Reply*/

typedef struct ifreq t_ifreq;
typedef struct ether_header t_eh;
typedef struct sockaddr_ll t_saddrll;
typedef struct iphdr t_iphdr;
typedef struct udphdr t_udphdr;
typedef struct icmphdr t_icmphdr;
typedef struct ether_arp t_earp;

#define ARP_PKT_LEN sizeof(t_eh) + sizeof(t_earp)

class PacketBuilder
{
private:
  int		_fd;
  t_pconf	_pconf;
  t_ifreq	_ipaddr;
  t_ifreq       _interface;
  t_ifreq       _mac;
  t_saddrll	_saddrll;
  t_eh		*_eh;
  t_iphdr	*_iph;
  t_udphdr	*_udph;
  t_earp	*_arph;
  t_icmphdr	*_icmph;
  char		_buffer[BUF_SIZE];
  char		_arpPacket[ARP_PKT_LEN];
  int		_len = 0;
public:
  PacketBuilder(int fd, t_pconf pconf);
  void		setEthernetHeader();
  void		setIPHeader(int protocol = IPPROTO_IP, int ttl=DEFAULT_TTL);
  void		setICMPHeader(int ttl=DEFAULT_TTL, int type = ICMP_ECHO);
  void		setIGMPHeader();
  void		setTCPHeader();
  void		setUDPHeader(int ttl=DEFAULT_TTL);
  void		setARPHeader();
  /* op values: */
  /* ARPOP_REQUEST	1 request to resolve address */
  /* ARPOP_REPLY	2 response to previous request */
  /* ARPOP_REVREQUEST	3 request protocol address given hardware */
  /* ARPOP_REVREPLY	4 response giving protocol address */
  /* ARPOP_INVREQUEST	8 request to identify peer */
  /* ARPOP_INVREPLY	9 response identifying peer */
  void		setPlayload(char *p);
  void		Send();
};

#endif /* PACKET_BUILDER_HH_ */
