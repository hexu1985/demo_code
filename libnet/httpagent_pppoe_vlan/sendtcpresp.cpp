 
#include "sendtcp.h"
#include <algorithm>

using std::min;

bool send_tcp_resp(const char *data, int len, 
		struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l)
{
	int req_payload_len = ntohs(ipptr->tot_len)-ipptr->ihl*4-tcpptr->doff*4;
	int nsend = 0; 
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	struct net_pppoe_hdr *ppphdr = NULL;
	unsigned short pppoe_payload_len = 0;
	libnet_ptag_t t;

	for (int i = 0; i < len; i += MAX_SEND_LEN) {
		nsend = min(MAX_SEND_LEN, len-i);
		eth_payload_len = 0;
		ppphdr = NULL;
		pppoe_payload_len = 0;

		// 构造TCP Segment
		t = libnet_build_tcp(
				ntohs(tcpptr->dest),                   /* source port */
				ntohs(tcpptr->source),                 /* destination port */
				ntohl(tcpptr->ack_seq)+i,              /* sequence number */
				ntohl(tcpptr->seq)+req_payload_len,    /* acknowledgement num */
				0x18,                                  /* control flags */
				17520,                                 /* window size */
				0,                                     /* checksum */
				0,                                     /* urgent pointer */
				LIBNET_TCP_H + nsend,                  /* TCP packet size */
				(uint8_t *) data + i,                  /* payload */
				nsend,                                 /* payload size */
				l,                                     /* libnet handle */
				0);                                    /* libnet id */
		if (t == -1)
		{
			fprintf(stderr, "[%d]Can't build TCP header: %s\n", i, libnet_geterror(l));
			goto bad;
		}

		// 构造IP datagram
		t = libnet_build_ipv4(
				LIBNET_IPV4_H + LIBNET_TCP_H + nsend,    /* length */
				0,                                       /* TOS */
				1691,                                    /* IP ID */
				0,                                       /* IP Frag */
				64,                                      /* TTL */
				IPPROTO_TCP,                             /* protocol */
				0,                                       /* checksum */
				ipptr->daddr,                            /* source IP */
				ipptr->saddr,                            /* destination IP */
				NULL,                                    /* payload */
				0,                                       /* payload size */
				l,                                       /* libnet handle */
				0);                                      /* libnet id */
		if (t == -1)
		{
			fprintf(stderr, "[%d]Can't build IP header: %s\n", i, libnet_geterror(l));
			goto bad;
		}

		// 构造ether
		if (vlan != NULL) {
			eth_payload_len = vlan_num * sizeof (struct net_vlan_hdr);
			memcpy(eth_payload, (uint8_t *) vlan, eth_payload_len);
		}

		if (pppoe != NULL) {
			//有PPPOE头的以太数据
			ppphdr = NULL;
			pppoe_payload_len = 0;
			pppoe_payload_len = LIBNET_TCP_H + LIBNET_IPV4_H + nsend  + 2 ;

			ppphdr = ( struct net_pppoe_hdr * ) (eth_payload + eth_payload_len);
			ppphdr->ver = 1;
			ppphdr->type = 1;
			ppphdr->code = 0;
			ppphdr->ssn_id = pppoe->ssn_id;
			ppphdr->length = htons (pppoe_payload_len);
			ppphdr->protocol = htons ( 0x0021 );

			eth_payload_len += sizeof(net_pppoe_hdr);
		}

		if (eth_payload_len) { 
			t = libnet_build_ethernet(
					eptr->ether_shost,                  /* ethernet destination */
					eptr->ether_dhost,                  /* ethernet source */
				ntohs(eptr->ether_type),
//				ETHERTYPE_IP,                       /* protocol type */
					eth_payload,                        /* payload */
					eth_payload_len,                    /* payload size */
					l,                                  /* libnet handle */
					0);
			if (t == -1)
			{
				printf("Can't build ethernet header: %s\n",
						libnet_geterror(l));
				goto bad;
			}
		} else {
			t = libnet_build_ethernet(
					eptr->ether_shost,                  /* ethernet destination */
					eptr->ether_dhost,                  /* ethernet source */
				ntohs(eptr->ether_type),
//				ETHERTYPE_IP,                       /* protocol type */
					NULL,                               /* payload */
					0,                                  /* payload size */
					l,                                  /* libnet handle */
					0);
			if (t == -1)
			{
				printf("Can't build ethernet header: %s\n",
						libnet_geterror(l));
				goto bad;
			}
		}

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

