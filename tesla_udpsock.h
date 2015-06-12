//
//  tesla_udpsock.h
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

#ifndef __tesla__tesla_udpsock__
#define __tesla__tesla_udpsock__

#include "tesla_sock.h"

#define tesla_udpsock tesla_sock
#define tesla_udpsock_set_recv_timeout tesla_sock_set_recv_timeout
#define tesla_udpsock_close tesla_sock_close
#define tesla_udpsock_destroy tesla_sock_destroy
#define tesla_udpsock_close_and_destroy tesla_sock_close_and_destroy

tesla_sock* tesla_udpsock_init(const char *host, int port);

ssize_t tesla_udpsock_send(tesla_sock *sock, char *data_buffer, size_t data_len);

ssize_t tesla_udpsock_recv(tesla_sock *sock, void *dest_buffer, size_t read_len);

#ifdef __tesla_udpsock__shortnames__
    #define tesla_sock_send tesla_udpsock_send
    #define tesla_sock_recv tesla_udpsock_recv
#endif


#endif /* defined(__tesla__tesla_udpsock__) */
