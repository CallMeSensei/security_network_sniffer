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

PacketBuilder::PacketBuilder(int fd, char *interface_name, int dmac[])
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

  //Etherner header
  std::memset(_buffer, 0, BUF_SIZE);
  _eh = (t_eh *) _buffer;
  _saddrll.sll_ifindex = interface.ifr_ifindex;
  _saddrll.sll_halen = ETH_ALEN;
  for (int i = 0; i < ETH_ALEN; i++)
    {
      _eh->ether_shost[i] = ((uint8_t *)&mac.ifr_hwaddr.sa_data)[i];
      _eh->ether_dhost[i] = dmac[i];
      _saddrll.sll_addr[i] = dmac[i];
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

void	PacketBuilder::setICMPHeader(char *sip, char *dip, int ttl, int type)
{
  //ICMP Header
  this->setIPHeader(sip, dip, IPPROTO_ICMP, ttl);
  _icmph = (t_icmphdr *) (_buffer + sizeof (t_iphdr) + sizeof (t_eh));
  _icmph->type = type;
  _icmph->code = 0;
  _icmph->un.echo.sequence = rand();
  _icmph->un.echo.id = rand();
  _icmph->checksum = 0;
  _len += sizeof(t_icmphdr);
}

void	PacketBuilder::setIGMPHeader()
{
  //IGMP Header
}

void	PacketBuilder::setTCPHeader()
{
  //TCP Header
}

void	PacketBuilder::setUDPHeader(char *sip, char *dip, int sport, int dport, int ttl)
{
  //UDP Header
  this->setIPHeader(sip, dip, IPPROTO_UDP, ttl);
  _udph = (t_udphdr *) (_buffer + sizeof(t_iphdr) + sizeof(t_eh));
  _udph->source = htons(sport);
  _udph->dest = htons(dport);
  _udph->check = 0;
  _udph->len = htons(_len - sizeof(t_eh) - sizeof(t_iphdr) + 8);
  _len += sizeof(t_udphdr);
}

void	PacketBuilder::setARPHeader(int smac[], int dmac[], char *sip, char *dip, int op)
{
  int	saddr[IP_V4_LEN];
  int	daddr[IP_V4_LEN];
  int	spoint;
  int	dpoint;
  char	tmp[IP_V4_LEN];

  for (int i = 0; i < IP_V4_LEN; i++)
    {
      for (spoint = 0; sip[spoint] != '.' && sip[spoint] != '\0'; spoint++);
      for (dpoint = 0; dip[dpoint] != '.' && dip[dpoint] != '\0'; dpoint++);
      std::memset(tmp, '\0', IP_V4_LEN);
      std::memcpy(tmp, sip, spoint);
      saddr[i] = atoi(tmp);
      std::memset(tmp, '\0', IP_V4_LEN);
      std::memcpy(tmp, dip, dpoint);
      daddr[i] = atoi(tmp);
      sip = &sip[spoint + 1];
      dip = &dip[dpoint + 1];
    }
  printf("%d.%d.%d.%d\n", saddr[0], saddr[1], saddr[2], saddr[3]);
  printf("%d.%d.%d.%d\n", daddr[0], daddr[1], daddr[2], daddr[3]);
  std::memset(_arpPacket, 0, ARP_PKT_LEN);

  //Ethernet Header
  _eh = (t_eh *) _buffer;
  //ARP Header
  _arph = (t_earp *) (_buffer + sizeof(t_eh));
  for (int i = 0; i < ETH_ALEN; i++)
    {
      _eh->ether_shost[i] = smac[i];
      _eh->ether_dhost[i] = dmac[i];
      _arph->arp_sha[i] = smac[i];
      _arph->arp_tha[i] = dmac[i];
      _saddrll.sll_addr[i] = dmac[i];
      if (i < IP_V4_LEN)
	{
	  _arph->arp_spa[i] = saddr[i];
	  _arph->arp_tpa[i] = daddr[i];
	}
    }
  _eh->ether_type = htons(ETH_P_ARP);

  _saddrll.sll_family = AF_PACKET;
  _arph = (t_earp *) (_buffer + sizeof(t_eh));
  _arph->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
  _arph->ea_hdr.ar_pro = htons(ETH_P_IP);
  _arph->ea_hdr.ar_hln = ETH_ALEN;
  _arph->ea_hdr.ar_pln = IP_V4_LEN;
  _arph->ea_hdr.ar_op = htons(op);
  _len = ARP_PKT_LEN;
}

void	PacketBuilder::setPlayload(char *p)
{
  //Data playload
  for(int i = 0; p[i] != '\0'; i++)
      _buffer[_len++] = p[i];
}

void	PacketBuilder::Send()
{
  int	sendtoResult;

  if (_isARP)
    sendtoResult = sendto(_fd, _arpPacket, _len, 0, (struct sockaddr*)&_saddrll, sizeof(t_saddrll));
  else
    sendtoResult = sendto(_fd, _buffer, _len, 0, (struct sockaddr*)&_saddrll, sizeof(t_saddrll));
  if (sendtoResult < 0)
    perror("Send");
}
