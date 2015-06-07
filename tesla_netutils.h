//
//  tesla_netutils.h
//  tesla
//
//  Created by Henry Pitcairn on 2/12/15.
//  Copyright (c) 2015 Entropy. All rights reserved.
//

/*
 A variety of utilities related to
 resolving domain names and reverse
 IP address lookups
 */


#ifndef __tesla__tesla_netutils__
#define __tesla__tesla_netutils__
#include <stddef.h>


/*
 Gets the first DNS record for a host
     hostname:
        The hostname to search for. If this is an IP address then
        no lookup will be performed and the hostname will be copied
        into ipaddr
     ipaddr:
        The buffer in which to store the first IP address found
     ipaddr_size:
        The size of ipaddr, this function will not write more than
        ipaddr_size-1 bytes to ipaddr
 returns 0 on success and 1 on failure.
 */
int tesla_dns_lookup_host(const char *hostname, char *ipaddr, size_t ipaddr_size);

/*
 Attempts a reverse DNS lookup on an IP address
    ipaddr:
        The IP address to lookup
    hostname:
        The buffer in which the result will be stored
    hostname_size:
        The size of the hostname buffer. The number of bytes
        copied to hostname will not exceed hostname_size-1
 returns 0 on success and 1 on failure
 */
int tesla_reverse_dns_lookup_host(const char *ipaddr, char *hostname, size_t hostname_size);

/*
 Generates a random ipv4 address
 This function is part of the code because this
 was alll taken from a part of the net code I
 wrote for the scanner I use to find interesing
 things on the interwebz. That needs major cleanup
 and a complete version will not be on Github for
 a little while.
    ip_addr:
        The buffer in which to store the ip address
    ipaddr_sz:
        The size of ip_addr
    blacklist:
        A NULL terminated list of IP addresses that cannot be used
        If set to NULL, any IP address string could
        be used. If used, MUST be NULL terminated of the function
        will begin reading outside of the array
    iterations:
        The number of times to try and produce an IP address
        that is not in blacklist before returning failure
 returns 0 on success and 1 on failure
 */
int tesla_get_rand_ipv4(char *ip_addr, size_t ipaddr_sz, char **blacklist, int iterations);

#endif /* defined(__tesla__tesla_netutils__) */
