#ifndef	__sendtcpresp_h
#define	__sendtcpresp_h

#include <libnet.h>

struct ipptr;
struct tcpptr;
struct ether_header;

bool send_tcp_rst(struct tcphdr *tcpptr, struct iphdr *ipptr, struct ether_header *eptr, libnet_t *l);

#endif
