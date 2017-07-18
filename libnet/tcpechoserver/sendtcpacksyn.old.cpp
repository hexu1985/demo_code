 
#include "sendtcp.h"

bool send_tcp_ack_syn(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct ether_header *eptr, libnet_t *l)
{
	libnet_ptag_t t;
	int c;

	// 构造TCP Segment
	t = libnet_build_tcp(
			ntohs(tcpptr->dest),                   /* source port */
			ntohs(tcpptr->source),                 /* destination port */
			ntohl(tcpptr->ack_seq),                /* sequence number */
			ntohl(tcpptr->seq)+1,                  /* acknowledgement num */
			0x12,                                  /* control flags */
			17520,                                 /* window size */
			0,                                     /* checksum */
			0,                                     /* urgent pointer */
			LIBNET_TCP_H,                          /* TCP packet size */
			NULL,                                  /* payload */
			0,                                     /* payload size */
			l,                                     /* libnet handle */
			0);                                    /* libnet id */
	if (t == -1)
	{
		fprintf(stderr, "Can't build TCP header: %s\n", libnet_geterror(l));
		goto bad;
	}

	// 构造IP datagram
	t = libnet_build_ipv4(
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
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
		fprintf(stderr, "Can't build IP header: %s\n", libnet_geterror(l));
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
		fprintf(stderr, "Can't build ethernet header: %s\n", libnet_geterror(l));
		goto bad;
	}

	// 发送报文
	/*
	 *  Write it to the wire.
	 */
	c = libnet_write(l);
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

	return true;

bad:
	libnet_clear_packet(l);
	return false;
}

bool send_tcp_ack_syn_raw(struct tcphdr *tcpptr, struct iphdr *ipptr, libnet_t *l)
{
	libnet_ptag_t t;
	int c;

	// 构造TCP Segment
	t = libnet_build_tcp(
			ntohs(tcpptr->dest),                   /* source port */
			ntohs(tcpptr->source),                 /* destination port */
			ntohl(tcpptr->ack_seq),                /* sequence number */
			ntohl(tcpptr->seq)+1,                  /* acknowledgement num */
			0x12,                                  /* control flags */
			17520,                                 /* window size */
			0,                                     /* checksum */
			0,                                     /* urgent pointer */
			LIBNET_TCP_H,                          /* TCP packet size */
			NULL,                                  /* payload */
			0,                                     /* payload size */
			l,                                     /* libnet handle */
			0);                                    /* libnet id */
	if (t == -1)
	{
		fprintf(stderr, "Can't build TCP header: %s\n", libnet_geterror(l));
		goto bad;
	}

	// 构造IP datagram
	t = libnet_build_ipv4(
			LIBNET_IPV4_H + LIBNET_TCP_H,            /* length */
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
		fprintf(stderr, "Can't build IP header: %s\n", libnet_geterror(l));
		goto bad;
	}

	// 发送报文
	/*
	 *  Write it to the wire.
	 */
	c = libnet_write(l);
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

	return true;

bad:
	libnet_clear_packet(l);
	return false;
}

