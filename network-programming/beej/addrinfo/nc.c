//
// Created by bagaswh on 5/6/25.
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

int main(const int argc, char *argv[]) {
    struct addrinfo hints, *res;
    int status;

    if (argc != 3) {
        fprintf(stderr, "usage: <host> <port>\n");
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }
    freeaddrinfo(&hints);

    const int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (connect(s, res->ai_addr, res->ai_addrlen) != 0) {
        fprintf(stderr, "connect: %s\n", strerror(errno));
    }

}
