 
#include <libnet.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <algorithm>

using std::min;

const int MAX_SEND_LEN = 1400;

bool send_tcp_resp(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, struct ether_header *eptr,
	libnet_t *l)
{
	int req_payload_len = ntohs(ipptr->tot_len)-ipptr->ihl*4-tcpptr->doff*4;
	int nsend = 0; 
	libnet_ptag_t t;
	for (int i = 0; i < len; i += MAX_SEND_LEN) {
		nsend = min(MAX_SEND_LEN, len-i);

		// 构造TCP Segment
		t = libnet_build_tcp(
				ntohs(tcpptr->dest),                   /* source port */
				ntohs(tcpptr->source),                 /* destination port */
				ntohl(tcpptr->ack_seq)+i,              /* sequence number */
				ntohl(tcpptr->seq)+req_payload_len,    /* acknowledgement num */
				0x18 | (nsend < MAX_SEND_LEN ? 1 : 0), /* control flags */
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

		// 构造Ether Frame
		t = libnet_build_ethernet(
				eptr->ether_shost,                  /* ethernet destination */
				eptr->ether_dhost,                  /* ethernet source */
				ETHERTYPE_IP,                       /* protocol type */
				NULL,                               /* payload */
				0,                                  /* payload size */
				l,                                  /* libnet handle */
				0);                                 /* libnet id */
		if (t == -1)
		{
			fprintf(stderr, "[%d]Can't build ethernet header: %s\n", i, libnet_geterror(l));
			goto bad;
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
			printf("Wrote %d byte TCP packet; check the wire.\n", c);
		}

		// 为下一个报文做准备
		libnet_clear_packet(l);
	}

	return true;

bad:
	libnet_clear_packet(l);
	return false;
}

bool send_tcp_resp_raw(const char *data, int len,
	struct tcphdr *tcpptr, struct iphdr *ipptr, libnet_t *l)
{
	int req_payload_len = ntohs(ipptr->tot_len)-ipptr->ihl*4-tcpptr->doff*4;
	int nsend = 0; 
	libnet_ptag_t t;
	for (int i = 0; i < len; i += MAX_SEND_LEN) {
		nsend = min(MAX_SEND_LEN, len-i);

		// 构造TCP Segment
		t = libnet_build_tcp(
				ntohs(tcpptr->dest),                   /* source port */
				ntohs(tcpptr->source),                 /* destination port */
				ntohl(tcpptr->ack_seq)+i,              /* sequence number */
				ntohl(tcpptr->seq)+req_payload_len,    /* acknowledgement num */
				0x18 | (nsend < MAX_SEND_LEN ? 1 : 0), /* control flags */
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
				0x4000,                                  /* IP Frag */
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
			printf("Wrote %d byte TCP packet; check the wire.\n", c);
		}

		// 为下一个报文做准备
		libnet_clear_packet(l);
	}

	return true;

bad:
	libnet_clear_packet(l);
	return false;
}
