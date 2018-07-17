#ifndef	__unp_sock_ntop_h
#define	__unp_sock_ntop_h

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

std::string sock_ntop(const struct sockaddr *, socklen_t);
std::string Sock_ntop(const struct sockaddr *, socklen_t);

#endif

