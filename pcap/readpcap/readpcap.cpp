/*
   Listing 2. Simple sniffer
   To compile: gcc readpcap.c -o readpcap -lpcap
   */
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXBYTES2CAPTURE 2048

void processPacket(u_char *arg, const struct pcap_pkthdr *pkthdr,
		const u_char *packet)
{
	int i = 0, *counter = (int *)arg;
	printf("Pcaket Count: %d\n", ++(*counter));
	printf("Received Packet Size: %d\n", pkthdr->len);
	printf("Capture Packet Size: %d\n", pkthdr->caplen);
	printf("Payload:\n");
	for (i=0; i<pkthdr->len; i++) {
		if ( isprint(packet[i]) )
			printf("%c ", packet[i]);
		else
			printf(". ");
		if ( (i%16 == 0 && i!=0) || i==pkthdr->len-1)
			printf("\n");
	}
	return;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: readpcap pcapfile\n");
		exit(1);
	}

	int i=0, count=0;
	pcap_t *descr = NULL;
	char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);

	/*以混杂模式打开网络设备*/
	descr = pcap_open_offline(argv[1], errbuf);
	if (descr == NULL) {
		printf("open pcap %s file error: %s\n", argv[1], errbuf);
		exit(1);
	}

	/*死循环并在每一次接收到数据包时调用回调函数processPacket()*/
	pcap_loop(descr, -1, processPacket, (u_char *)&count);

	return 0;
}
