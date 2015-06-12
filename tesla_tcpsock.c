//
//  tesla_tcpsock.c
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

#include "tesla_tcpsock.h"
#include "tesla_netutils.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>

tesla_sock* tesla_tcpsock_init(char *host, int port) {
    return tesla_sock_init(host, port, SOCK_STREAM);
}

int tesla_tcpsock_set_connect_timeout(tesla_sock *sock, unsigned int connect_timeout) {
    if (sock->proto == SOCK_DGRAM) {
        fprintf(stderr, "[!] Cannot set timeout on tesla_sock at %p: it is a datagram sock and is connectionless\n", sock);
        return 1;
    }
    if (sock->connected) {
        fprintf(stderr, "[!] Cannot set timeout on tesla_sock at %p: it has already been connected \n", sock);
        return 1;
    }
    sock->connect_timeout = connect_timeout;
    if (connect_timeout) {
        fcntl(sock->sockfd, F_SETFL, fcntl(sock->sockfd, F_GETFL, 0) | O_NONBLOCK);
        sock->blocking = 0;
        FD_SET(sock->sockfd, &sock->s_fdset);
    }
    else
        sock->blocking = 1;
    return 0;
}

int tesla_tcpsock_set_send_timeout(tesla_sock *sock, unsigned int timeout_secs) {
    fprintf(stderr, "[!] A send timeout is being set on a tesla_sock at %p, but it UDP send operations are non-blocking\n", sock);
    if (tesla_tcpsock_assert_unconnected(sock)) {
        struct timeval timeout;
        timeout.tv_sec = timeout_secs;
        timeout.tv_usec = 0;
        if (setsockopt(sock->sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0)
            return 1;
        return 0;
    }
    return 1;
}

int tesla_tcpsock_assert_connected(tesla_sock *sock) {
    if (!sock->connected) {
        fprintf(stderr, "[!] tesla_sock at %p is not connected\n", sock);
        return 0;
    }
    return 1;
}

int tesla_tcpsock_assert_unconnected(tesla_sock *sock) {
    if (sock->connected) {
        fprintf(stderr, "[!] tesla_sock at %p is already connected\n", sock);
        return 0;
    }
    return 1;
}

ssize_t tesla_tcpsock_send(tesla_sock *sock, char *data_buffer, size_t data_len) {
    if (sock->proto != SOCK_STREAM) {
        fprintf(stderr, "[!] tesla_tcpsock_send cannot be used on udp sock at %p\n", sock);
        return -1;
    }
    if (tesla_tcpsock_assert_connected(sock)) {
        ssize_t ret;
        ret = send(sock->sockfd, data_buffer, data_len, 0);
        if (ret < 0)
            fprintf(stderr, "[!] Send failed on tesla_sock at %p: %s\n", sock, strerror(errno));
        return ret;
    }
    return -1;
}

ssize_t tesla_tcpsock_recv(tesla_sock *sock, void *dest_buffer, size_t read_len) {
    if (sock->proto != SOCK_STREAM) {
        fprintf(stderr, "[!] tesla_tcpsock_recv cannot be used on udp sock at %p\n", sock);
        return -1;
    }
    if (tesla_tcpsock_assert_connected(sock)) {
        return recv(sock->sockfd, dest_buffer, read_len, 0);
    }
    return 0;
}

int tesla_tcpsock_connect(tesla_sock *sock) {
    if (sock->proto == SOCK_DGRAM) {
        fprintf(stderr, "[!] tesla_sock_connect cannot be used on udp sock at %p\n", sock);
        return -1;
    }
    if (tesla_tcpsock_assert_unconnected(sock)) {
        int success;
        success = connect(sock->sockfd, (struct sockaddr*)&sock->server_addr, sizeof(struct sockaddr_in));
        if (success != 0 && sock->blocking) {
            fprintf(stderr, "[!] Connect() failed: %s\n", strerror(errno));
            return 1;
        }
        if (sock->blocking) {
            struct timeval tv;
            tv.tv_sec = sock->connect_timeout;
            tv.tv_usec = 0;
            if (select(sock->sockfd+1, NULL, &sock->s_fdset, NULL, &tv) < 1) {
                fprintf(stderr, "[!] tesla_sock at %p timed out waiting %d secs to connect to %s:%d\n", sock, sock->connect_timeout, sock->addr, sock->port);
                return 1;
            }
        }
        sock->connected = 1;
    }
    return 0;
}
