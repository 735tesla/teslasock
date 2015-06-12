//
//  tesla_udpsock.c
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

#include "tesla_udpsock.h"
#include "tesla_netutils.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

tesla_udpsock *tesla_udpsock_init(const char *host, int port) {
    return tesla_sock_init(host, port, SOCK_DGRAM);
}

ssize_t tesla_udpsock_send(tesla_sock *sock, char *data_buffer, size_t data_len) {
    if (sock->proto != SOCK_DGRAM) {
        fprintf(stderr, "[!] tesla_udpsock_send cannot be used on tcp sock at %p\n", sock);
        return -1;
    }
    ssize_t ret = sendto(sock->sockfd, data_buffer, data_len, 0, (struct sockaddr*)&sock->server_addr, (socklen_t)sizeof(struct sockaddr));
    if (ret < 0) {
        fprintf(stderr, "[!] Send failed on tesla_sock at %p: %s\n", sock, strerror(errno));
    }
    return ret;
}

ssize_t tesla_udpsock_recv(tesla_sock *sock, void *dest_buffer, size_t read_len) {
    if (sock->proto != SOCK_DGRAM) {
        fprintf(stderr, "[!] tesla_udpsock_send cannot be used on tcp sock at %p\n", sock);
        return -1;
    }
    socklen_t len = sizeof(struct sockaddr);
    ssize_t ret = recvfrom(sock->sockfd, dest_buffer, read_len, 0, (struct sockaddr*)&sock->server_addr, &len);
    if (ret < 0) {
        fprintf(stderr, "[!] Recv failed on tesla_udpsock at %p: %s\n", sock, strerror(errno));
    }
    return ret;
}
