//
//  tesla_udpsocket.h
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

#ifndef __tesla__tesla_udpsocket__
#define __tesla__tesla_udpsocket__

#include "tesla_sock.h"

#define tesla_udpsocket tesla_socket
#define tesla_udpsocket_set_recv_timeout tesla_socket_set_recv_timeout
#define tesla_udpsocket_close tesla_socket_close
#define tesla_udpsocket_destroy tesla_socket_destroy
#define tesla_udpsocket_close_and_destroy tesla_socket_close_and_destroy

tesla_socket* tesla_udpsocket_init(const char *host, int port);

ssize_t tesla_udpsocket_send(tesla_socket *socket, char *data_buffer, size_t data_len);

ssize_t tesla_udpsocket_recv(tesla_socket *socket, void *dest_buffer, size_t read_len);

#ifdef __tesla_udpsocket__shortnames__
    #define tesla_socket_send tesla_udpsocket_send
    #define tesla_socket_recv tesla_udpsocket_recv
#endif


#endif /* defined(__tesla__tesla_udpsocket__) */
