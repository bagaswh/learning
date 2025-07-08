#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define CONN_MESSAGE_BUF 1024
#define BACKLOG 10

void sigchld_handler(int s) {
    int saved_errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0) {
    }
    errno = saved_errno;
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: server port\n");
        return 1;
    }

    struct addrinfo hints = {0};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *res;
    int status;
    if ((status = getaddrinfo(NULL, argv[1], &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    const int server_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_sock == -1) {
        fprintf(stderr, "socket: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    if (bind(server_sock, res->ai_addr, res->ai_addrlen) == -1) {
        fprintf(stderr, "bind: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (listen(server_sock, BACKLOG) == -1) {
        fprintf(stderr, "listen: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    freeaddrinfo(res);

    printf("Server listening on port %s...\n", argv[1]);

    struct sockaddr_storage remote_addr;
    socklen_t remote_addr_size = sizeof remote_addr;
    // const char *msg = "Bagas was here";
    // int len = strlen(msg);
    while (1) {
        memset(&remote_addr, 0, sizeof remote_addr);
        remote_addr_size = sizeof remote_addr;

        const int remote_sock = accept(server_sock, (struct sockaddr *)&remote_addr, &remote_addr_size);
        if (remote_sock == -1) {
            fprintf(stderr, "accept: %s\n", strerror(errno));
            continue;
        }

        char buf[CONN_MESSAGE_BUF];
        while (1) {
            memset(buf, 0, CONN_MESSAGE_BUF);

            int bytes_recv = recv(remote_sock, buf, CONN_MESSAGE_BUF, 0);
            if (bytes_recv == -1) {
                fprintf(stderr, "recv: %s\n", strerror(errno));
                break;
            } else if (bytes_recv == 0) {
                close(remote_sock);
                break;
            } else {
                buf[bytes_recv] = '\0';
                const int bytes_sent = send(remote_sock, buf, bytes_recv, 0);
                if (bytes_sent == -1) {
                    fprintf(stderr, "send: %s\n", strerror(errno));
                    break;
                }
            }
        }

        close(remote_sock);
    }

    close(server_sock);
    return 1;
}
