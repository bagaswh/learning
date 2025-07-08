#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
  struct sockaddr_in sa;
  struct sockaddr_in6 sa6;
  inet_pton(AF_INET, "1.1.1.1", &(sa.sin_addr));

  // convert back
  char ip4[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
  printf("%d, %s\n", sa.sin_addr.s_addr, ip4);
}