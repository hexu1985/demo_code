#ifndef	__sendtcpresp_h
#define	__sendtcpresp_h

#include <libnet.h>

struct ipptr;
struct tcpptr;
struct ether_header;

bool send_tcp_resp(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, struct ether_header *eptr,
	libnet_t *l);

bool send_tcp_resp_raw(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, libnet_t *l);

#endif
