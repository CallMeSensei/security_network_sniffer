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

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#include <cstring>

typedef struct ifreq t_ifreq;
typedef struct ether_header t_eh;
typedef struct sockaddr_ll t_saddrll;
typedef struct iphdr t_iphdr;
typedef struct udphdr t_udphdr;
typedef struct s_arphdr
{
  unsigned char	ar_hrd;/* format of hardware address*/
  unsigned char	ar_pro;/* format of protocol address*/
  unsigned char ar_hln;/* length of hardware address*/
  unsigned char ar_pln;/* length of protocol address*/
  unsigned char ar_op;/* ARP opcode (command)*/
  unsigned char ar_sha[ETH_ALEN];/* sender hardware address*/
  unsigned char ar_sip[4];/* sender IP address*/
  unsigned char ar_tha[ETH_ALEN];/* target hardware address*/
  unsigned char ar_tip[4];/* target IP address*/
}t_arphdr;

#define BUF_SIZE 2048
#define DEFAULT_PORT 4242
#define DEFAULT_TTL 42

class PacketBuilder
{
private:
  int		_fd;
  t_ifreq	_ipaddr;
  t_eh		*_eh;
  t_saddrll	_saddrll;
  t_iphdr	*_iph;
  t_udphdr	*_udph;
  t_arphdr	*_arph;
  char		_buffer[BUF_SIZE];
  int		_len;
public:
  PacketBuilder(int fd, char *interface, int macaddr[]);
  void		setIPHeader(char *sip, char *dip, int protocol, int ttl=DEFAULT_TTL); //Set sip to NULL for use real ip
  void		setUDPHeader(char *sip, char *dip, int sport=DEFAULT_PORT, int dport=DEFAULT_PORT, int ttl=DEFAULT_TTL);
  void		setARPHeader(int smac[], int dmac[], char *sip, char *dip);
  void		setPlayload(char *p);
  void		Send();
};

#endif /* PACKET_BUILDER_HH_ */
