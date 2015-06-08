//
//  tesla_netutils.c
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//


#include "tesla_netutils.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <netdb.h>


int tesla_dns_lookup_host(const char *hostname, char *ipaddr, size_t ipaddr_size) {
    struct sockaddr_in sa;
    if (inet_pton(AF_INET, hostname, &sa.sin_addr) == 1) {
        strlcpy(ipaddr, hostname, ipaddr_size);
        return 0;
    }
    struct hostent *he;
    struct in_addr **addr_list;
    if ((he = gethostbyname(hostname)) == NULL)
        return 1;
    addr_list = (struct in_addr**)he->h_addr_list;
    if (addr_list[0] == NULL)
        return 1;
    strlcpy(ipaddr, inet_ntoa(*addr_list[0]), ipaddr_size);
    return 0;
}


int tesla_reverse_dns_lookup_host(const char *ipaddr, char *hostname, size_t hostname_size) {
    struct hostent *hent;
    struct in_addr addr;
    if(!inet_aton(ipaddr, &addr))
        return 1;
    if (!(hent = gethostbyaddr(&addr.s_addr, sizeof(addr.s_addr), AF_INET)) && hent != NULL )
        strlcpy(hostname, hent->h_name, hostname_size);
    else
        return 1;
    return 0;
}

int tesla_get_rand_ipv4(char *ip_addr, size_t ipaddr_sz, char **blacklist, int iterations) {
    memset(ip_addr, 0, ipaddr_sz);
    if (iterations-- == 0)
        return 1;
    int ip[4];
    FILE *fp = NULL;
    if ((fp = fopen("/dev/urandom", "rb")) == NULL)
        return 1;
    int rnd;
    for (int i=0; i<4; ++i) {
        if ((rnd = fgetc(fp)) == EOF) { // REALLY shouldn't happen
            fclose(fp);
            return 1;
        }
        ip[i] = rnd % 255;
    }
    fclose(fp);
    snprintf(ip_addr, ipaddr_sz, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    if (blacklist) {
        char *bad_ip = NULL;
        while ((bad_ip = *blacklist++) != NULL)
            if (strcmp(bad_ip, ip_addr) != 0)
                return tesla_get_rand_ipv4(ip_addr, ipaddr_sz, blacklist, iterations);
    }
    return 0;
}

int straddr(const struct sockaddr *addr, void *restrict buf, size_t buf_size) {
	memset(buf, 0, buf_size);
	if (addr->sa_family == AF_INET6)
		return (inet_ntop(addr->sa_family, &((struct sockaddr_in6*)addr)->sin6_addr, buf, (socklen_t)buf_size) == NULL) ? 1 : 0;
	else if (addr->sa_family == AF_INET)
		return (inet_ntop(addr->sa_family, &((struct sockaddr_in*)addr)->sin_addr.s_addr, buf, (socklen_t)buf_size) == NULL) ? 1 : 0;
	return 1;
}
