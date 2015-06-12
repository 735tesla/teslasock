
//
//  tesla_tcpsock.h
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

#ifndef __tesla_tcpsock__
#define __tesla_tcpsock__

#include "tesla_sock.h"

#define tesla_tcpsock tesla_sock
#define tesla_tcpsock_set_recv_timeout tesla_sock_set_recv_timeout
#define tesla_tcpsock_close tesla_sock_close
#define tesla_tcpsock_destroy tesla_sock_destroy
#define tesla_tcpsock_close_and_destroy tesla_sock_close_and_destroy

tesla_sock* tesla_tcpsock_init(char *host, int port);

int tesla_tcpsock_set_connect_timeout(tesla_sock *sock, unsigned int timeout_secs);

int tesla_tcpsock_set_send_timeout(tesla_sock *sock, unsigned int timeout_secs);

int tesla_tcpsock_assert_connected(tesla_sock *sock);

int tesla_tcpsock_assert_unconnected(tesla_sock *sock);

int tesla_tcpsock_connect(tesla_sock *sock);

ssize_t tesla_tcpsock_send(tesla_sock *sock, char *data_buffer, size_t data_len);

ssize_t tesla_tcpsock_recv(tesla_sock *sock, void *dest_buffer, size_t read_len);

#ifdef __tesla_tcpsock__shortnames__
	#define tesla_sock_connect tesla_tcpsock_connect
	#define tesla_sock_set_connect_timeout tesla_tcpsock_set_connect_timeout
	#define tesla_sock_set_send_timeout tesla_tcpsock_set_send_timeout
	#define tesla_sock_assert_connected tesla_tcpsock_assert_connected
	#define tesla_sock_assert_unconnected tesla_tcpsock_assert_unconnected
	#define tesla_sock_send tesla_tcpsock_send
	#define tesla_sock_recv tesla_tcpsock_recv
#endif

#endif /* defined(__tesla_tcpsock__) */
