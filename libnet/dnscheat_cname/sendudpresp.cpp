#include <libnet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>

bool send_udp_resp(const uint8_t *data, int len,
	struct udphdr *udpptr, struct iphdr *ipptr, struct ether_header *eptr,
	libnet_t *l)
{
	libnet_ptag_t t;
	int c;
	t = libnet_build_udp(
			ntohs(udpptr->dest),                /* source port */
			ntohs(udpptr->source),              /* destination port */
			LIBNET_UDP_H + len,					/* packet size */
			0,                                  /* checksum */
			(uint8_t *) data,                   /* payload */
			len,                                /* payload size */
			l,                                  /* libnet handle */
			0);                                 /* libnet id */
	if (t == -1)
	{
		printf("Can't build UDP header (at port %d): %s\n", 
				ntohs(udpptr->source), libnet_geterror(l));
		goto bad;
	}

	t = libnet_build_ipv4(
			LIBNET_IPV4_H + LIBNET_UDP_H + len,         /* length */
			0,                                          /* TOS */
			242,                                        /* IP ID */
			0,                                          /* IP Frag */
			64,                                         /* TTL */
			IPPROTO_UDP,                                /* protocol */
			0,                                          /* checksum */
			ipptr->daddr,                               /* source IP */
			ipptr->saddr,                               /* destination IP */
			NULL,                                       /* payload */
			0,                                          /* payload size */
			l,                                          /* libnet handle */
			0);
	if (t == -1)
	{
		printf("Can't build IP header: %s\n", libnet_geterror(l));
		goto bad;
	}

	t = libnet_build_ethernet(
			eptr->ether_shost,                  /* ethernet destination */
			eptr->ether_dhost,                  /* ethernet source */
			ETHERTYPE_IP,                       /* protocol type */
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

	c = libnet_write(l); 
	if (c == -1)
	{
		printf("write error: %s\n", libnet_geterror(l));
	}
	else
	{
		printf("wrote %d byte UDP packet to port %d\n", c, 
				ntohs(udpptr->source));
	}

	libnet_clear_packet(l);
	return true;

bad:
	libnet_clear_packet(l);
	return false;
}

bool send_udp_resp_raw(const uint8_t *data, int len,
	struct udphdr *udpptr, struct iphdr *ipptr, libnet_t *l)
{
	libnet_ptag_t t;
	int c;
	t = libnet_build_udp(
			ntohs(udpptr->dest),                /* source port */
			ntohs(udpptr->source),              /* destination port */
			LIBNET_UDP_H + len,					/* packet size */
			0,                                  /* checksum */
			(uint8_t *) data,                   /* payload */
			len,                                /* payload size */
			l,                                  /* libnet handle */
			0);                                 /* libnet id */
	if (t == -1)
	{
		printf("Can't build UDP header (at port %d): %s\n", 
				ntohs(udpptr->source), libnet_geterror(l));
		goto bad;
	}

	t = libnet_build_ipv4(
			LIBNET_IPV4_H + LIBNET_UDP_H + len,         /* length */
			0,                                          /* TOS */
			242,                                        /* IP ID */
			0,                                          /* IP Frag */
			64,                                         /* TTL */
			IPPROTO_UDP,                                /* protocol */
			0,                                          /* checksum */
			ipptr->daddr,                               /* source IP */
			ipptr->saddr,                               /* destination IP */
			NULL,                                       /* payload */
			0,                                          /* payload size */
			l,                                          /* libnet handle */
			0);
	if (t == -1)
	{
		printf("Can't build IP header: %s\n", libnet_geterror(l));
		goto bad;
	}

	c = libnet_write(l); 
	if (c == -1)
	{
		printf("write error: %s\n", libnet_geterror(l));
	}
	else
	{
		printf("wrote %d byte UDP packet to port %d\n", c, 
				ntohs(udpptr->source));
	}

	libnet_clear_packet(l);
	return true;

bad:
	libnet_clear_packet(l);
	return false;
}
