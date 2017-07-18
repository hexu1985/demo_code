#include "sendudpresp.h"
#include <libnet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>

bool send_udp_resp_pppoe_vlan(const uint8_t *data, int len,
	struct udphdr *udpptr, struct iphdr *ipptr, struct net_pppoe_hdr *pppoe,
	struct net_vlan_hdr *vlan, int vlan_num, struct ether_header *eptr,
	libnet_t *l)
{
	libnet_ptag_t t = 0;
	int c = 0;
	uint8_t eth_payload[128] = {0};
	int eth_payload_len = 0;
	struct net_pppoe_hdr *ppphdr = NULL;
	unsigned short pppoe_payload_len = 0;

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

	// 构造ether
	if (vlan != NULL) {
		eth_payload_len = vlan_num * sizeof (struct net_vlan_hdr);
		memcpy(eth_payload, (uint8_t *) vlan, eth_payload_len);
	}

	if (pppoe != NULL) {
		//有PPPOE头的以太数据
		ppphdr = NULL;
		pppoe_payload_len = 0;
		pppoe_payload_len = LIBNET_UDP_H + LIBNET_IPV4_H + len  + 2 ;

		ppphdr = ( struct net_pppoe_hdr * ) (eth_payload + eth_payload_len);
		ppphdr->ver = 1;
		ppphdr->type = 1;
		ppphdr->code = 0;
		ppphdr->ssn_id = pppoe->ssn_id;
		ppphdr->length = htons (pppoe_payload_len);
		ppphdr->protocol = htons ( 0x0021 );

		eth_payload_len += sizeof(net_pppoe_hdr);
	}

	if (eth_payload_len != 0) { 
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
			ntohs(eptr->ether_type),
//			ETHERTYPE_IP,                       /* protocol type */
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
