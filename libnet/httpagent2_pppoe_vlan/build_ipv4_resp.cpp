#include "sendtcp.h"
#include <string>
#include <stdexcept>

using namespace std;

void build_ipv4_resp(
		struct iphdr *ipptr, 
		uint16_t ip_len,
		uint8_t prot,
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l)
{
	// 构造IP datagram
	libnet_ptag_t t = libnet_build_ipv4(
			ip_len,                                  /* length */
			0,                                       /* TOS */
			1691,                                    /* IP ID */
			0,                                       /* IP Frag */
			64,                                      /* TTL */
			prot,                                    /* protocol */
			0,                                       /* checksum */
			ipptr->daddr,                            /* source IP */
			ipptr->saddr,                            /* destination IP */
			payload,                                 /* payload */
			payload_s,                               /* payload size */
			l,                                       /* libnet handle */
			0);                                      /* libnet id */
	if (t == -1)
	{
		throw runtime_error("build_ipv4_resp error: "+string(libnet_geterror(l)));
	}
}

