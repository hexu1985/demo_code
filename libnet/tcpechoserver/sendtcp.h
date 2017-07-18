#ifndef __sendtcp_h
#define __sendtcp_h

#include <libnet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <linux/ip.h>
#include <linux/tcp.h>

bool send_tcp_ack(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_raw(struct tcphdr *tcpptr, struct iphdr *ipptr, libnet_t *l);

bool send_tcp_ack_syn(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_syn_raw(struct tcphdr *tcpptr, struct iphdr *ipptr, libnet_t *l);

bool send_tcp_resp(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, struct ether_header *eptr,
	libnet_t *l);

bool send_tcp_resp_raw(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, libnet_t *l);

#endif
