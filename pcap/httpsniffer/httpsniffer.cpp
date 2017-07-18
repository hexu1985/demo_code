/* Simple ARP sniffer
 * To compile: gcc tcpsniffer.c -o tcppsniffer -lpcap
 * Run as root!
 * */
#include "httpget.h"
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <iostream>

using std::cout;
using std::endl;

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
	struct iphdr *ipptr = NULL;
	struct tcphdr *tcpptr = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);
	struct in_addr addr;

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,
			0, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "tcp and dst port 80", 1, mask);
	pcap_setfilter(descr, &filter);

	Httpget_header httpget_hdr;
	while (1){
		int ret = pcap_next_ex(descr, &pkthdr, &packet);
		if (ret < 0) {
			printf("pcap_next_ex error: %s\n", pcap_geterr(descr));
			exit(1);
		}
		if (packet == NULL)
			continue;

		ipptr = (struct iphdr *)(packet + 14);

		tcpptr = (struct tcphdr *) (packet + 14 + ipptr->ihl*4);

		if (!httpget_unpack((uint8_t *) packet + 14 + ipptr->ihl*4 + tcpptr->doff*4, 
				(uint8_t *) packet + pkthdr->caplen, &httpget_hdr)) {
			continue;
		}

		printf("Received Packet Size: %d bytes\n", pkthdr->len);
		printf("Capture Packet Size: %d bytes\n", pkthdr->caplen);
		printf("the IP packets version: %d\n", ipptr->version); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->tot_len));
		printf ("the IP protocol is %d\n", ipptr->protocol);
		addr.s_addr = ipptr->daddr;
		printf ("Destination IP: %s\n", inet_ntoa(addr));    
		addr.s_addr = ipptr->saddr;
		printf ("Source IP: %s\n", inet_ntoa(addr));

		printf ("Destination port : %d\n", ntohs(tcpptr->dest));
		printf ("Source port : %d\n", ntohs(tcpptr->source));
		printf ("the seq of packet is %u\n", ntohl(tcpptr->seq));

		cout << "HTTP version: " << httpget_hdr.version << '\n';
		cout << "HTTP method: " << httpget_hdr.method << '\n';
		cout << "HTTP uri: " << httpget_hdr.uri << '\n';
		cout << "HTTP host: " << httpget_hdr.host << '\n';
		cout << "HTTP user_agent: " << httpget_hdr.user_agent << '\n';
		cout << endl;
	}
	return 0;
}

