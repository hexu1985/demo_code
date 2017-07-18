 
#include "sendtcp.h"
#include <algorithm>

using std::min;

bool send_tcp_data(const char *data, int len, 
		struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l)
{
	int req_payload_len = ntohs(ipptr->tot_len)-ipptr->ihl*4-tcpptr->doff*4;
	int nsend = 0; 
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;

	for (int i = 0; i < len; i += MAX_SEND_LEN) {
		nsend = min(MAX_SEND_LEN, len-i);
		eth_payload_len = 0;

		// 构造TCP Segment
		build_tcp_resp(
				tcpptr,
				ntohl(tcpptr->ack_seq)+i,              /* sequence number */
				ntohl(tcpptr->seq)+req_payload_len,    /* acknowledgement num */
				(TH_ACK | TH_PUSH),                    /* control flags */
				(uint8_t *) data + i,                  /* payload */
				nsend,                                 /* payload size */
				l);

		// 构造IP datagram
		build_ipv4_resp(
				ipptr,
				LIBNET_IPV4_H + LIBNET_TCP_H + nsend,    /* length */
				IPPROTO_TCP,                             /* protocol */
				NULL,                                    /* payload */
				0,                                       /* payload size */
				l);                                      /* libnet handle */

		// 构造pppoe and vlan header
		eth_payload_len = build_pppoe_vlan_resp(
				eth_payload, sizeof (eth_payload),
				pppoe, vlan, vlan_num);

		// 构造ethernet frame
		build_ethernet_resp(
				eptr,
				(eth_payload_len > 0 ? eth_payload : NULL),
				eth_payload_len,
				l);

		// 发送报文
		/*
		 *  Write it to the wire.
		 */
		int c = libnet_write(l);
		if (c == -1)
		{
			fprintf(stderr, "Write error: %s\n", libnet_geterror(l));
			goto bad;
		}
		else
		{
#ifndef NDEBUG
			printf("Wrote %d byte TCP packet; check the wire.\n", c);
#endif
		}

		// 为下一个报文做准备
		libnet_clear_packet(l);
	}

	return true;

bad:
	libnet_clear_packet(l);
	return false;
}

