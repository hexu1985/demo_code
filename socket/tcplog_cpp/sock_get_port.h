#ifndef	__unp_sock_get_port_h
#define	__unp_sock_get_port_h

#include <netinet/in.h>
#include <arpa/inet.h>

int sock_get_port(const struct sockaddr *, socklen_t);

#endif

