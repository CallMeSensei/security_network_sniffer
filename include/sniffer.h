/*
**
**	Network security project - file: sniffer.h
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-01 17:49:31
**
*/

#ifndef _SNIFFER_H_
#define _SNIFFER_H_

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define BUF_SIZE 2048

#include <sys/types.h> //socket, recvfrom
#include <sys/socket.h> //socket, recvfrom
#include <arpa/inet.h> //htons
#include <stdio.h> //perror, printf
#include <net/ethernet.h> //ETH_P_ALL, struct ethhdr
#include <unistd.h> //close
#include <linux/ip.h> //struct iphdr

typedef struct sockaddr_in t_sockaddr_in;
typedef struct iphdr t_iphdr;

#endif /* _SNIFFER_H_ */
