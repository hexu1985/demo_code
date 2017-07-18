/* Simple ARP sniffer
 * To compile: gcc ipsniffer.c -o ipsniffer -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>

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
	struct ip *ipptr = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,
			512, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "ip", 1, mask);
	pcap_setfilter(descr, &filter);
	while (1){
		int ret = pcap_next_ex(descr, &pkthdr, &packet);
		if (ret < 0) {
			printf("pcap_next_ex error: %s\n", pcap_geterr(descr));
			exit(1);
		}
		ipptr = (struct ip *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf("\n\nthe IP packets version: %d\n", ipptr->ip_v); 
		printf ("the IP packets total_length is :%d\n", ntohs(ipptr->ip_len));
		printf ("the IP protocol is %d\n", ipptr->ip_p);
		printf ("Destination IP: %s\n", inet_ntoa(ipptr->ip_dst));    
		printf ("Source IP: %s\n", inet_ntoa(ipptr->ip_src));
	}
	return 0;
}
