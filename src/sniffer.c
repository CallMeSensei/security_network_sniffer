/*
**
**	Network security project - file: sniffer.c
**
**	Author: alexandre.jallon@epitech.eu
**	Created on: 2017-11-01 17:49:17
**
*/

#include "../include/sniffer.h"

int			main()
{
  int			fd;
  struct sockaddr	addr;
  int			addrlen;
  int			recvlen;
  char			buffer[BUF_SIZE];

  fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); //ETH_P_ALL = receive all protocol
  if (fd < 0)
    {
      perror("Socket");
      return (EXIT_FAILURE);
    }
  while (1)
    {
      addrlen = sizeof addr;
      recvlen = recvfrom(fd, &buffer, BUF_SIZE, 0, &addr, (socklen_t*)&addrlen);
      if (recvlen < 0)
	{
	  printf("recvfrom failed\n");
	  return (EXIT_FAILURE);
	}
      printf("Recv: %s\n", buffer);
    }
  if (close(fd) < 0)
    {
      printf("Close failed");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
  
