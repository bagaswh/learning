//
// Created by bagaswh on 5/10/25.
//

#ifndef DHCP_CLIENT_H
#define DHCP_CLIENT_H

uint32_t xid();
int send_discover(const struct sockaddr_in*);
int inet_pton_with_err(const char *ipv4, uint32_t *dest);

#endif //DHCP_CLIENT_H
