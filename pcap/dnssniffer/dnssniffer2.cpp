/* Simple TCP sniffer
 * To compile: gcc udpsniffer.c -o udppsniffer -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <libnet.h>
#include <string>
#include "dns_header.h"

using std::string;

#define MAXBYTES2CAPTURE 2048
int main(int argc, char *argv[])
{
	int i=0;
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr = NULL;
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct libnet_ipv4_hdr *ipptr = NULL;
	struct libnet_udp_hdr *udpptr = NULL;
	struct Dns_header *dnsptr = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);
	struct in_addr addr;

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,
			512, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "udp and port 53", 1, mask);
	pcap_setfilter(descr, &filter);
	while (1){
		packet = NULL;
		int ret = pcap_next_ex(descr, &pkthdr, &packet);
		if (ret < 0) {
			printf("pcap_next_ex error: %s\n", pcap_geterr(descr));
			exit(1);
		}
		if (packet == NULL)
			continue;
		ipptr = (struct libnet_ipv4_hdr *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf("\n\nthe IP packets version: %d\n", ipptr->ip_v); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->ip_len));
		printf ("the IP protocol is %d\n", ipptr->ip_p);
		printf ("Destination IP: %s\n", inet_ntoa(ipptr->ip_dst));    
		printf ("Source IP: %s\n", inet_ntoa(ipptr->ip_src));

		udpptr = (struct libnet_udp_hdr *) (packet + 14 + ipptr->ip_hl*4);
		printf ("Destination port : %d\n", ntohs(udpptr->uh_dport));
		printf ("Source port : %d\n", ntohs(udpptr->uh_sport));
		printf ("the len of udp packet is %u\n", ntohs(udpptr->uh_ulen));

		dnsptr = (struct Dns_header *) (packet + 14 + ipptr->ip_hl*4 + sizeof (libnet_udp_hdr));
		printf ("the Dns transaction id: %x\n", ntohs(dnsptr->id));
		printf ("the Dns flags: %x\n", ntohs(dnsptr->flags));
		printf ("the Dns questions: %d\n", ntohs(dnsptr->num_q));
		printf ("the Dns Answer RRs: %d\n", ntohs(dnsptr->num_answ_rr));
		printf ("the Dns Authority RRs: %d\n", ntohs(dnsptr->num_auth_rr));
		printf ("the Dns Additional RRs: %d\n", ntohs(dnsptr->num_addi_rr));

		if (ntohs(dnsptr->num_q) != 1)
			continue;

		uint8_t *dns_body = (uint8_t *) (packet + 14 + ipptr->ip_hl*4 + 
				sizeof (libnet_udp_hdr) + sizeof (Dns_header));
		string name;
		int dns_qname_len = dns_qname(dns_body, packet+pkthdr->caplen, name);
		printf ("the Dns query: %s(%d)\n", name.c_str(), dns_qname_len);

		if (dns_qname_len < 0) {
			continue;
		}
		printf ("the Dns query type: %x\n", 
				ntohs(*(uint16_t *)(dns_body+dns_qname_len)));
		printf ("the Dns query class: %x\n", 
				ntohs(*(uint16_t *)(dns_body+dns_qname_len+2)));

	}
	return 0;
}
