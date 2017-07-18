/* Simple ARP sniffer
 * To compile: gcc tcpsniffer.c -o tcppsniffer -lpcap
 * Run as root!
 * */
#include "httpget.h"
#include "sendtcprst.h"
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <linux/ip.h>
#include <linux/tcp.h>
#include <libnet.h>
#include <iostream>
#include <algorithm>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define MAXBYTES2CAPTURE 2048

int main(int argc, char *argv[])
{
	int i=0;
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	char *errbuf = new char[std::max(PCAP_ERRBUF_SIZE, LIBNET_ERRBUF_SIZE)];
	pcap_t *descr = NULL;
	struct pcap_pkthdr *pkthdr;
	const unsigned char *packet = NULL;
	struct ether_header *eptr = NULL;  /* net/ethernet.h */
	struct iphdr *ipptr = NULL;
	struct tcphdr *tcpptr = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);
	struct in_addr addr;
	libnet_t *send_descr;
	libnet_ptag_t *send_tag;

	string host = "www.sina.com";
	if (argc < 2){
		printf("Usage: httpblock <interface> [host]\n\texample: httpblock eth0 www.sina.com\n");
		exit(1);
	}

	if (argc == 3) {
		host = argv[2];
	}

	// libnet dev open
	send_descr = libnet_init(
            LIBNET_LINK,                            /* injection type */
            argv[1],                                /* network interface */
            errbuf);                                /* error buffer */

    if (send_descr == NULL)
    {
        printf("libnet_init() failed: %s", errbuf);
        exit(EXIT_FAILURE);
    }

	// libpcap dev open
	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1,
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

		eptr = (struct ether_header *) packet;

		ipptr = (struct iphdr *) (packet + 14);

		tcpptr = (struct tcphdr *) (packet + 14 + ipptr->ihl*4);

		if (!httpget_unpack((uint8_t *) packet + 14 + ipptr->ihl*4 + tcpptr->doff*4, 
				(uint8_t *) packet + pkthdr->caplen, &httpget_hdr)) {
			continue;
		}

		if (httpget_hdr.host == host) {
			cout << "match " << host << endl;
			if (!send_tcp_rst(tcpptr, ipptr, eptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
		}

#ifndef NDEBUG
		printf("Received Packet Size: %d bytes\n", pkthdr->len);
		printf("Capture Packet Size: %d bytes\n", pkthdr->caplen);

		uint8_t *ptr = eptr->ether_dhost;
		i = ETHER_ADDR_LEN;
		printf("Destination Address:  ");
		do{
			printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
		}while(--i>0);
		printf("\n");

		ptr = eptr->ether_shost;
		i = ETHER_ADDR_LEN;
		printf("Source Address:  ");
		do{
			printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
		}while(--i>0);

		printf("\n");
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
#endif
	}

	return 0;
}

