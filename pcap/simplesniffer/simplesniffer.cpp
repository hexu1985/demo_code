/*
   Listing 2. Simple sniffer
   To compile: gcc simplesniffer.c -o simplesinffer -lpcap
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

int main()
{
	int i=0, count=0;
	pcap_t *descr = NULL;
	char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);

	/*获取第一个适合捕获的网络设备名称*/
	device = pcap_lookupdev(errbuf);
	printf("Opening device %s\n", device);

	/*以混杂模式打开网络设备*/
	descr = pcap_open_live(device, MAXBYTES2CAPTURE, 1, 512, errbuf);
	if (descr == NULL) {
		printf("open %s live error: %s\n", device, errbuf);
		exit(1);
	}

	/*死循环并在每一次接收到数据包时调用回调函数processPacket()*/
	pcap_loop(descr, -1, processPacket, (u_char *)&count);

	return 0;
}
