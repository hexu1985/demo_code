/* Simple ARP sniffer
 * To compile: gcc tcpsniffer.c -o tcppsniffer -lpcap
 * Run as root!
 * */
#include "sendtcp.h"
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

using namespace std;

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
	in_addr_t addr;
	uint16_t port;
	libnet_t *send_descr;
	libnet_ptag_t *send_tag;
	int next_index = 0;

	if (argc != 4){
		cerr << "Usage: ipsniffer <interface> <ip> <port>\n";
		exit(1);
	}

	addr = inet_addr(argv[2]);
	if (addr == INADDR_NONE) {
		cerr << "invalid ip " << argv[2] << '\n';
		exit(1);
	}

	port = atoi(argv[3]);

#ifdef SEND_LOCAL
	// libnet dev open
	send_descr = libnet_init(
            LIBNET_RAW4,                            /* injection type */
            argv[1],                                /* network interface */
            errbuf);                                /* error buffer */
#else
	// libnet dev open
	send_descr = libnet_init(
            LIBNET_LINK,                            /* injection type */
            argv[1],                                /* network interface */
            errbuf);                                /* error buffer */
#endif

    if (send_descr == NULL)
    {
        cerr << "libnet_init() failed: " << errbuf << '\n';
		exit(1);
    }

	// libpcap dev open
	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0, 0, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "tcp", 1, mask);
	pcap_setfilter(descr, &filter);

	while (1){
		packet = NULL;
		eptr = NULL;
		ipptr = NULL;
		tcpptr = NULL;
		next_index = 0;

		int ret = pcap_next_ex(descr, &pkthdr, &packet);
		if (ret < 0) {
			printf("pcap_next_ex error: %s\n", pcap_geterr(descr));
			exit(1);
		}
		if (packet == NULL)
			continue;

		eptr = (struct ether_header *) packet;
		next_index = sizeof (struct ether_header);

		if (ntohs(eptr->ether_type) != 0x0800)	// only ipv4
			continue;

		ipptr = (struct iphdr *)(packet + next_index);
		next_index += ipptr->ihl*4;

		// filter dest ip
		if (ipptr->daddr != addr)
			continue;

		if (ipptr->protocol != 6)	// only tcp
			continue;	

		tcpptr = (struct tcphdr *) (packet + next_index);
		next_index += tcpptr->doff*4;

		// filter dest port
		if (port != ntohs(tcpptr->dest))
			continue;

		if (tcpptr->syn && !tcpptr->ack) {
#ifdef SEND_LOCAL
			if (!send_tcp_ack_syn_raw(tcpptr, ipptr, send_descr)) {
				cerr << "send_tcp_ack_syn fault!\n";
				exit(1);
			}
#else
			if (!send_tcp_ack_syn(tcpptr, ipptr, eptr, send_descr)) {
				cerr << "send_tcp_ack_syn fault!\n";
				exit(1);
			}
#endif
			continue;
		}

		if (tcpptr->psh && tcpptr->ack) {
#ifdef SEND_LOCAL
			if (!send_tcp_ack_raw(tcpptr, ipptr, send_descr)) {
				cerr << "send_tcp_ack_syn fault!\n";
				exit(1);
			}
#else
			if (!send_tcp_ack(tcpptr, ipptr, eptr, send_descr)) {
				cerr << "send_tcp_ack_syn fault!\n";
				exit(1);
			}
#endif
		}

		int req_payload_len = ntohs(ipptr->tot_len)-ipptr->ihl*4-tcpptr->doff*4;
		char *req_payload = (char *) (packet + next_index);
		if (req_payload_len != 0) {
#ifdef SEND_LOCAL
			if (!send_tcp_resp_raw(req_payload, req_payload_len,
					tcpptr, ipptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
#else
			if (!send_tcp_resp(req_payload, req_payload_len,
					tcpptr, ipptr, eptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
#endif
		}
	}

	return 0;
}

