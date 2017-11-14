/*
**
**	Network security project - file: PacketBuilder.cpp
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-11 21:33:56
**
*/

#include <iostream>

#include "PacketBuilder.hh"

PacketBuilder::PacketBuilder(int fd, char *interface_name, int macaddr[])
{
  t_ifreq	interface;
  t_ifreq	mac;
  
  _fd = fd;
  std::memset(&interface, 0, sizeof interface);
  std::strcpy(interface.ifr_name, interface_name);
  if (ioctl(fd, SIOCGIFINDEX, &interface) < 0)
    perror("SIOCGIFINDEX");
  std::memset(&mac, 0, sizeof mac);
  std::strcpy(mac.ifr_name, interface_name);
  if (ioctl(fd, SIOCGIFHWADDR, &mac) < 0)
    perror("SIOCGIFHWADDR");
  std::memset(&_ipaddr, 0, sizeof _ipaddr);
  std::strcpy(_ipaddr.ifr_name, interface_name);
  if (ioctl(fd, SIOCGIFADDR, &_ipaddr) < 0)
    perror("SIOCGIFADDR");

  // ETH header
  _eh = (t_eh *) _buffer;
  std::memset(_buffer, 0, BUF_SIZE);
  _saddrll.sll_ifindex = interface.ifr_ifindex;
  _saddrll.sll_halen = ETH_ALEN;
  for (int i = 0; i < ETH_ALEN; i++)
    {
      _eh->ether_shost[i] = ((uint8_t *)&mac.ifr_hwaddr.sa_data)[i];
      _eh->ether_dhost[i] = macaddr[i];
      _saddrll.sll_addr[i] = macaddr[i];
    }
  _eh->ether_type = htons(ETH_P_IP);
  _len += sizeof(t_eh);
}

void	PacketBuilder::setIPHeader(char *sip, char *dip, int protocol, int ttl)
{
  //IP Header
  _iph = (t_iphdr *) (_buffer + sizeof(t_eh));
  _iph->ihl = 5;
  _iph->version = 4;
  _iph->tos = 16;
  _iph->id = htons(12345);
  _iph->ttl = ttl;
  _iph->protocol = protocol;
  if (sip == NULL)
    _iph->saddr = inet_addr(inet_ntoa(((struct sockaddr_in *)&_ipaddr.ifr_addr)->sin_addr));
  else
    _iph->saddr = inet_addr(sip);
  _iph->daddr = inet_addr(dip);
  _iph->tot_len = htons(_len - sizeof(t_eh));
  _len += sizeof(t_iphdr);
}

void	PacketBuilder::setUDPHeader(char *sip, char *dip, int sport, int dport, int ttl)
{
  //UDP Header
  this->setIPHeader(sip, dip, 17, ttl);
  _udph = (t_udphdr *) (_buffer + sizeof(t_iphdr) + sizeof(t_eh));
  _udph->source = htons(sport);
  _udph->dest = htons(dport);
  _udph->check = 0;
  _udph->len = htons(_len - sizeof(t_eh) - sizeof(t_iphdr) + 8);
  _len += sizeof(t_udphdr);
}

void	PacketBuilder::setARPHeader(int smac[], int dmac[], char *sip, char *dip) //Doesn't work
{
  int	saddr[4];
  int	daddr[4];
  int	spoint;
  int	dpoint;
  char	tmp[4];

  for (int i = 0; i < 4; i++)
    {
      for (spoint = 0; sip[spoint] != '.' && sip[spoint] != '\0'; spoint++);
      for (dpoint = 0; dip[dpoint] != '.' && dip[dpoint] != '\0'; dpoint++);
      std::memset(tmp, '\0', 4);
      std::memcpy(tmp, sip, spoint);
      saddr[i] = atoi(tmp);
      std::memset(tmp, '\0', 4);
      std::memcpy(tmp, dip, dpoint);
      daddr[i] = atoi(tmp);
      sip = &sip[spoint + 1];
      dip = &dip[dpoint + 1];
    }
  printf("%d.%d.%d.%d\n", saddr[0], saddr[1], saddr[2], saddr[3]);
  printf("%d.%d.%d.%d\n", daddr[0], daddr[1], daddr[2], daddr[3]);
  //ARP Header
  _saddrll.sll_family = PF_PACKET;
  _saddrll.sll_protocol = htons(ETH_P_ARP);
  _arph = (t_arphdr *) (_buffer + sizeof(t_iphdr) + sizeof(t_eh));
  _arph->ar_hrd = ARPHRD_ETHER;
  _arph->ar_pro = htons(ETH_P_IP);
  _arph->ar_hln = ETH_ALEN;
  _arph->ar_pln = 4;
  _arph->ar_op = ARPOP_REQUEST;
  for (int i = 0; i < ETH_ALEN; i++)
    {
      _arph->ar_sha[i] = smac[i];
      _arph->ar_tha[i] = dmac[i];
      if (i < 4)
	{
	  _arph->ar_sip[i] = saddr[i];
	  _arph->ar_tip[i] = daddr[i];
	}
    }
  _len += sizeof(t_arphdr);
}

void	PacketBuilder::setPlayload(char *p)
{
  //Data playload
  for(int i = 0; p[i] != '\0'; i++)
      _buffer[_len++] = p[i];
}

void	PacketBuilder::Send()
{
  if (sendto(_fd, _buffer, _len, 0, (struct sockaddr*)&_saddrll, sizeof(struct sockaddr_ll)) < 0)
    perror("Send");
}
