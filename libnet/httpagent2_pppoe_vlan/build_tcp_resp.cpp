#include "sendtcp.h"
#include <string>
#include <stdexcept>

using namespace std;

void build_tcp_resp(
		struct tcphdr *tcpptr, 
		uint32_t seq,
		uint32_t ack,
		uint8_t control, 
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l)
{
	// 构造TCP Segment
	libnet_ptag_t t = libnet_build_tcp(
			ntohs(tcpptr->dest),                   /* source port */
			ntohs(tcpptr->source),                 /* destination port */
			seq,                                   /* sequence number */
			ack,                                   /* acknowledgement num */
			control,                               /* control flags */
			17520,                                 /* window size */
			0,                                     /* checksum */
			0,                                     /* urgent pointer */
			LIBNET_TCP_H + payload_s,              /* TCP packet size */
			(uint8_t *) payload,                   /* payload */
			payload_s,                             /* payload size */
			l,                                     /* libnet handle */
			0);                                    /* libnet id */
	if (t == -1)
	{
		throw runtime_error("build_tcp_resp error: "+string(libnet_geterror(l)));
	}
}
