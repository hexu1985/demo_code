/* Check datalink type
 * To compile: gcc ipsniffer.c -o ipsniffer -lpcap
 * Run as root!
 * */
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

struct DLT_description {
	int dlt_type;
	const char *dlt_desc;
};

struct DLT_description dlt_descriptions[] = {
	{DLT_NULL, "BSD loopback encapsulation"},
	{DLT_EN10MB, "Ethernet (10Mb)"},
	{DLT_EN3MB, "Experimental Ethernet (3Mb)"},
	{DLT_AX25, "Amateur Radio AX.25"},
	{DLT_PRONET, "Proteon ProNET Token Ring"},
	{DLT_CHAOS, "Chaos"},
	{DLT_IEEE802, "802.5 Token Ring"},
	{DLT_ARCNET, "ARCNET, with BSD-style header"},
	{DLT_SLIP, "Serial Line IP"},
	{DLT_PPP, "Point-to-point Protocol"},
	{DLT_FDDI, "FDDI"}
};

#define MAXBYTES2CAPTURE 2048
int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("Usage: checkdlt <interface>\n");
		exit(1);
	}

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,
			512, errbuf);
	if (descr == NULL) {
		printf("open %s error: %s\n", argv[1], errbuf);
		exit(1);
	}

	int i = pcap_datalink(descr);
	printf("%s's datalink type[%d]: %s\n", argv[1], 
			dlt_descriptions[i].dlt_type, dlt_descriptions[i].dlt_desc);

	return 0;
}

