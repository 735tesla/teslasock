
//
//  tesla_tcpsocket.h
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

#ifndef __tesla_tcpsocket__
#define __tesla_tcpsocket__

#include "tesla_sock.h"

#define tesla_tcpsocket tesla_socket
#define tesla_tcpsocket_set_recv_timeout tesla_socket_set_recv_timeout
#define tesla_tcpsocket_close tesla_socket_close
#define tesla_tcpsocket_destroy tesla_socket_destroy
#define tesla_tcpsocket_close_and_destroy tesla_socket_close_and_destroy

tesla_socket* tesla_tcpsocket_init(char *host, int port);

int tesla_tcpsocket_set_connect_timeout(tesla_socket *socket, unsigned int timeout_secs);

int tesla_tcpsocket_set_send_timeout(tesla_socket *socket, unsigned int timeout_secs);

int tesla_tcpsocket_assert_connected(tesla_socket *socket);

int tesla_tcpsocket_assert_unconnected(tesla_socket *socket);

int tesla_tcpsocket_connect(tesla_socket *socket);

ssize_t tesla_tcpsocket_send(tesla_socket *socket, char *data_buffer, size_t data_len);

ssize_t tesla_tcpsocket_recv(tesla_socket *socket, void *dest_buffer, size_t read_len);

#ifdef __tesla_tcpsocket__shortnames__
	#define tesla_socket_connect tesla_tcpsocket_connect
	#define tesla_socket_set_connect_timeout tesla_tcpsocket_set_connect_timeout
	#define tesla_socket_set_send_timeout tesla_tcpsocket_set_send_timeout
	#define tesla_socket_assert_connected tesla_tcpsocket_assert_connected
	#define tesla_socket_assert_unconnected tesla_tcpsocket_assert_unconnected
	#define tesla_socket_send tesla_tcpsocket_send
	#define tesla_socket_recv tesla_tcpsocket_recv
#endif

#endif /* defined(__tesla_tcpsocket__) */
