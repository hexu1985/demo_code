#ifndef	__sendudpresp_h
#define	__sendudpresp_h

#include <libnet.h>

struct ipptr;
struct udpptr;
struct ether_header;

bool send_udp_resp(const uint8_t *data, int len,
	struct udphdr *udpptr, struct iphdr *ipptr, struct ether_header *eptr,
	libnet_t *l);

bool send_udp_resp_raw(const uint8_t *data, int len,
	struct udphdr *udpptr, struct iphdr *ipptr, libnet_t *l);

#endif

