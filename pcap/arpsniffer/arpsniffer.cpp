/* Simple ARP sniffer
 * To compile: gcc arpsniffer.c -o arpsniff -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//ARP Header, (assuming Ethernet+ipv4)
#define ARP_REQUEST 1
#define ARP_REPLY 2
typedef struct arphdr {
	u_int16_t htype; //hardware type
	u_int16_t ptype; //protocol type
	u_char hlen; //hardware address length
	u_char plen; //protocol address length
	u_int16_t oper; //operation code
	u_char sha[6]; //sender hardware address
	u_char spa[4]; //sender ip address
	u_char tha[6]; //target hardware address
	u_char tpa[4]; //target ip address
} arphdr_t;

#define MAXBYTES2CAPTURE 2048
int main(int argc, char *argv[])
{
	int i=0;
	bpf_u_int32 netaddr=0, mask=0;
	struct bpf_program filter;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr = NULL;
	struct pcap_pkthdr pkthdr;
	const unsigned char *packet = NULL;
	arphdr_t *arpheader = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);

	if (argc != 2){
		printf("Usage: arpsniffer <interface>\n");
		exit(1);
	}

	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,
			512, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "arp", 1, mask);
	pcap_setfilter(descr, &filter);
	while (1){
		packet = pcap_next(descr, &pkthdr);
		if (packet == NULL)
			continue;
		arpheader = (struct arphdr *)(packet + 14);
		printf("\n\nReceived Packet Size: %d bytes\n", pkthdr.len);
		printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ?
			"Ethernet" : "Unknown");
		printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ?
			"Ethernet" : "Unknown");
		printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST) ?
				"ARP Request" : "ARP Reply");
		if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x0800) {
			printf("Sender MAC: ");
			for (i=0; i<6; i++) printf("%02x:", arpheader->sha[i]);
			printf("\nSender IP: ");
			for (i=0; i<4; i++) printf("%d.", arpheader->spa[i]);
			printf("\nTarget MAC: ");
			for (i=0; i<6; i++) printf("%02x:", arpheader->tha[i]);
			printf("\nTarget IP: ");
			for (i=0; i<4; i++) printf("%d.", arpheader->tpa[i]);
			printf("\n");
		}
	}
	return 0;
}
