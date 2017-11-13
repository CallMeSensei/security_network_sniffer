/*
**
**	Network security project - file: sniffer.h
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-01 17:49:31
**
*/

#ifndef _SNIFFER_HH_
#define _SNIFFER_HH_

#define BUF_SIZE 2048

#include <sys/types.h> //socket, recvfrom
#include <sys/socket.h> //socket, recvfrom
#include <arpa/inet.h> //htons
#include <stdio.h> //perror, printf
#include <net/ethernet.h> //ETH_P_ALL, struct ethhdr
#include <unistd.h> //close
#include <linux/ip.h> //struct iphdr

typedef struct sockaddr_in t_sockaddr_in;

#endif /* _SNIFFER_HH_ */
