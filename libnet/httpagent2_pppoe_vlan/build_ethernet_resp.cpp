#include "sendtcp.h"
#include <string>
#include <stdexcept>

using namespace std;

void build_ethernet_resp(
		struct ether_header *eptr,
		const uint8_t *payload,
		uint32_t payload_s,
		libnet_t *l)
{
	libnet_ptag_t t = libnet_build_ethernet(
			eptr->ether_shost,                  /* ethernet destination */
			eptr->ether_dhost,                  /* ethernet source */
			ntohs(eptr->ether_type),			/* protocol type */
			payload,                            /* payload */
			payload_s,                          /* payload size */
			l,                                  /* libnet handle */
			0);
	if (t == -1)
	{
		throw runtime_error("build_ethernet_resp error: "+string(libnet_geterror(l)));
	}
}
