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

PacketBuilder::PacketBuilder(int fd, t_pconf pconf)
{
  _fd = fd;
  _pconf = pconf;
  std::memset(&_interface, 0, sizeof _interface);
  std::strcpy(_interface.ifr_name, _pconf.interface);
  if (ioctl(fd, SIOCGIFINDEX, &_interface) < 0)
    printf(COLOR_RED "[-] Set interface failed (SIOCGIFINDEX): %s\n" COLOR_RESET, strerror(errno));
  std::memset(&_mac, 0, sizeof _mac);
  std::strcpy(_mac.ifr_name, _pconf.interface);
  if (ioctl(fd, SIOCGIFHWADDR, &_mac) < 0)
    printf(COLOR_RED "[-] Set mac failed (SIOCGIFHWADDR): %s\n" COLOR_RESET, strerror(errno));
  std::memset(&_ipaddr, 0, sizeof _ipaddr);
  std::strcpy(_ipaddr.ifr_name, _pconf.interface);
  if (ioctl(fd, SIOCGIFADDR, &_ipaddr) < 0)
    printf(COLOR_RED "[-] Set ipaddr failed (SIOCGIFADDR): %s\n" COLOR_RESET, strerror(errno));
  std::memset(_buffer, 0, BUF_SIZE);
  std::memset(_arpPacket, 0, ARP_PKT_LEN);
  if (_pconf.ip_s == NULL)
    _pconf.ip_s = create_string(inet_ntoa(((struct sockaddr_in *)&_ipaddr.ifr_addr)->sin_addr));
  if (_pconf.mac_s[0] < 0)
    for (int i = 0; i < ETH_ALEN; i++)
      _pconf.mac_s[i] = ((uint8_t *)&_mac.ifr_hwaddr.sa_data)[i];
}

void	PacketBuilder::setEthernetHeader()
{
  //Ethernet header
  if (strcmp(_pconf.packet, "ARP") == 0)
    _eh = (t_eh *) _arpPacket;
  else
    _eh = (t_eh *) _buffer;
  _saddrll.sll_ifindex = _interface.ifr_ifindex;
  _saddrll.sll_halen = ETH_ALEN;
  for (int i = 0; i < ETH_ALEN; i++)
    {
      _eh->ether_shost[i] = _pconf.mac_s[i];
      _eh->ether_dhost[i] = _pconf.mac_d[i];
      _saddrll.sll_addr[i] = _pconf.mac_d[i];
    }
  printf(COLOR_GREEN "[+] ETH Packet created\n" COLOR_RESET);
  printf("Interface: %s\n", _pconf.interface);
  if (strcmp(_pconf.packet, "ARP") == 0)
    _eh->ether_type = htons(ETH_P_ARP);
  else
    _eh->ether_type = htons(ETH_P_IP);
  _len += sizeof(t_eh);
  print_mac_addr("\tMAC source addr:\t", _pconf.mac_s);
  print_mac_addr("\tMAC target addr:\t", _pconf.mac_d);
}

void	PacketBuilder::setIPHeader(int protocol, int ttl)
{
  //IP Header
  this->setEthernetHeader();
  _iph = (t_iphdr *) (_buffer + sizeof(t_eh));
  _iph->ihl = 5;
  _iph->version = 4;
  _iph->tos = 16;
  _iph->id = htons(12345);
  _iph->ttl = ttl;
  _iph->protocol = protocol;
  if (_pconf.ip_s == NULL)
    _iph->saddr = inet_addr(inet_ntoa(((struct sockaddr_in *)&_ipaddr.ifr_addr)->sin_addr));
  else
    _iph->saddr = inet_addr(_pconf.ip_s);
  _iph->daddr = inet_addr(_pconf.ip_d);
  _iph->tot_len = htons(_len - sizeof(t_eh));
  _len += sizeof(t_iphdr);
  printf(COLOR_GREEN "[+] IP Packet created\n" COLOR_RESET);
  printf("\tIP source addr:\t%s\n", _pconf.ip_s);
  printf("\tIP target addr:\t%s\n", _pconf.ip_d);
}

void	PacketBuilder::setICMPHeader(int ttl, int type)
{
  //ICMP Header
  this->setIPHeader(IPPROTO_ICMP, ttl);
  _icmph = (t_icmphdr *) (_buffer + sizeof (t_iphdr) + sizeof (t_eh));
  _icmph->type = type;
  _icmph->code = 0;
  _icmph->un.echo.sequence = rand();
  _icmph->un.echo.id = rand();
  _icmph->checksum = 0; //TODO calculate checksum
  _len += sizeof(t_icmphdr);
  printf(COLOR_GREEN "[+] ICMP Packet created\n" COLOR_RESET);
}

void	PacketBuilder::setIGMPHeader()
{
  //IGMP Header
  //TODO
  printf(COLOR_YELLOW "[*] Not yet implemented\n" COLOR_RESET);
}

void	PacketBuilder::setTCPHeader()
{
  //TCP Header
  //TODO
  printf(COLOR_YELLOW "[*] Not yet implemented\n" COLOR_RESET);
}

void	PacketBuilder::setUDPHeader(int ttl)
{
  //UDP Header
  this->setIPHeader(IPPROTO_UDP, ttl);
  _udph = (t_udphdr *) (_buffer + sizeof(t_iphdr) + sizeof(t_eh));
  _udph->source = htons(_pconf.port_s);
  _udph->dest = htons(_pconf.port_d);
  _udph->check = 0;
  _udph->len = htons(_len - sizeof(t_eh) - sizeof(t_iphdr) + 8);
  _len += sizeof(t_udphdr);
  printf(COLOR_GREEN "[+] UDP Packet created\n" COLOR_RESET);
  printf("\tSource port:\t%d\n", _pconf.port_s);
  printf("\tTarget port:\t%d\n", _pconf.port_d);
}

void	PacketBuilder::setARPHeader()
{
  int	ip_s[IP_V4_LEN];
  int	ip_d[IP_V4_LEN];

  //ARP Header
  this->setEthernetHeader();
  _arph = (t_earp *) (_arpPacket + sizeof(t_eh));
  set_ip_addr(_pconf.ip_s, &ip_s[0]);
  set_ip_addr(_pconf.ip_d, &ip_d[0]);
  for (int i = 0; i < ETH_ALEN; i++)
    {
      _arph->arp_sha[i] = _pconf.mac_s[i];
      _arph->arp_tha[i] = _pconf.mac_d[i];
      _saddrll.sll_addr[i] = _pconf.mac_d[i];
      if (i < IP_V4_LEN)
	{
	  _arph->arp_spa[i] = ip_s[i];
	  _arph->arp_tpa[i] = ip_d[i];
	}
    }
  _saddrll.sll_family = AF_PACKET;
  _arph->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
  _arph->ea_hdr.ar_pro = htons(ETH_P_IP);
  _arph->ea_hdr.ar_hln = ETH_ALEN;
  _arph->ea_hdr.ar_pln = IP_V4_LEN;
  _arph->ea_hdr.ar_op = htons(_pconf.op);
  _len = ARP_PKT_LEN;
  printf(COLOR_GREEN "[+] ARP Packet created\n" COLOR_RESET);
  printf("Opeartion: %d\n", _pconf.op);
  print_ip_addr("\tIP source addr:\t", ip_s);
  print_ip_addr("\tIP target addr:\t", ip_d);
}

void	PacketBuilder::setPlayload(char *p)
{
  for(int i = 0; p[i] != '\0'; i++)
      _buffer[_len++] = p[i];
}

void	PacketBuilder::Send()
{
  int	sendtoResult;

  if (strcmp(_pconf.packet, "ARP") == 0)
    sendtoResult = sendto(_fd, _arpPacket, _len, 0, (struct sockaddr*)&_saddrll, sizeof(t_saddrll));
  else
    sendtoResult = sendto(_fd, _buffer, _len, 0, (struct sockaddr*)&_saddrll, sizeof(t_saddrll));
  if (sendtoResult < 0)
    printf(COLOR_RED "[-] Send failed: %s\n" COLOR_RESET, strerror(errno));
}
