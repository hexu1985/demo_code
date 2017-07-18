#ifndef __sendtcp_h
#define __sendtcp_h

#include <libnet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>
#include <netinet/tcp.h>

bool send_tcp_ack(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_syn(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_resp(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, struct ether_header *eptr,
	libnet_t *l);

bool send_tcp_ack_fin1(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_fin2(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l);

#define MAX_SEND_LEN 1400

#endif
