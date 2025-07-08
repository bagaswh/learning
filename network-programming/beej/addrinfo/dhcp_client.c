// Improved DHCP Client in C - Following Beej's Network Programming
// Author: Bagas Wahyu Hidayah
// Date: 5/11/2025

#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define DHCP_OPTIONS_MAX_SIZE 312
#define MAX_IPV4_LENGTH 15 // "255.255.255.255"

struct dhcp_client_packet {
    uint8_t op, htype, hlen, hops;
    uint32_t xid;
    uint16_t secs, flags;
    uint32_t ciaddr, yiaddr, siaddr, giaddr;
    uint8_t chaddr[16];
    uint8_t sname[64];
    uint8_t file[128];
    uint8_t options[DHCP_OPTIONS_MAX_SIZE];
};

uint32_t xid() {
    uint32_t random_xid;
    FILE *urandom = fopen("/dev/urandom", "rb");
    if (urandom) {
        fread(&random_xid, sizeof(random_xid), 1, urandom);
        fclose(urandom);
        return random_xid;
    }
    return rand();
}

int send_discover(const struct sockaddr_in *local_addr) {
    struct dhcp_client_packet packet = {0};
    packet.op = 1;
    packet.htype = 1;
    packet.hlen = 6;
    packet.xid = xid();
    packet.flags = htons(0x8000);

    struct sockaddr_in dest_addr = {
            .sin_family = AF_INET, .sin_port = htons(67), .sin_addr.s_addr = htonl(INADDR_BROADCAST)};

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        return perror("socket"), EXIT_FAILURE;

    int broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
        return perror("setsockopt"), EXIT_FAILURE;

    if (bind(sock, (struct sockaddr *) local_addr, sizeof *local_addr) < 0)
        return perror("bind"), EXIT_FAILURE;

    printf("xid: %d\n", packet.xid);

    if (sendto(sock, &packet, sizeof packet, 0, (struct sockaddr *) &dest_addr, sizeof dest_addr) < 0)
        return perror("sendto"), EXIT_FAILURE;

    close(sock);
    return EXIT_SUCCESS;
}

struct sockaddr_in *select_interface(const char *arg) {
    struct ifaddrs *ifaddr;
    if (getifaddrs(&ifaddr) == -1)
        return perror("getifaddrs"), NULL;

    struct ifaddrs *selected = NULL;
    for (struct ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
            if ((arg == NULL && (strcmp(ifa->ifa_name, "lo") != 0)) || (arg != NULL && strcmp(ifa->ifa_name, arg) == 0)) {
                selected = ifa;
                break;
            }
        }
    }

    if (!selected)
        return fprintf(stderr, "No suitable interface found\n"), NULL;

    struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));
    if (addr)
        memcpy(addr, selected->ifa_addr, sizeof(struct sockaddr_in));

    freeifaddrs(ifaddr);
    return addr;
}

int main(const int argc, char *argv[]) {
    struct sockaddr_in *local_addr = NULL;

    if (argc < 2) {
        fprintf(stderr, "Using default network interface...\n");
        local_addr = select_interface(NULL);
    } else {
        if (strlen(argv[1]) > MAX_IPV4_LENGTH) {
            fprintf(stderr, "IP address too long\n");
            return EXIT_FAILURE;
        }

        if ((local_addr = select_interface(argv[1])) == NULL) {
            fprintf(stderr, "Failed to find suitable interface\n");
            return EXIT_FAILURE;
        }
    }

    if (local_addr == NULL)
        return EXIT_FAILURE;

    printf("local addr: %s\n", inet_ntoa(local_addr->sin_addr));

    if (send_discover(local_addr) != EXIT_SUCCESS)
        fprintf(stderr, "send_discover failed\n");

    free(local_addr);
    return EXIT_SUCCESS;
}
