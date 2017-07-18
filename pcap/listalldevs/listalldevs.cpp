#include "pcap.h"
#include <stdlib.h>
#include <stdio.h>

int main()//取得网络设备列表
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	//取得网络设备列表
	if(pcap_findalldevs(&alldevs,errbuf)==-1)
	{
		fprintf(stderr,"Error in pcap_findalldevs:%s\n",errbuf);
		exit(1);
	}
	//显示网络设备列表
	for(d=alldevs;d;d=d->next)
	{
		printf("%d",++i);
		printf("    ");
		printf("%s",d->name);
		printf("     ");
		if(d->description)
			printf("(%s)\n",d->description);
		else
			printf("(No description available)\n");
	}
	if(i==0)
	{
		printf("\nNo interfaces found!Make sure WinPcap is installed.\n");
		return 128;
	}
	pcap_freealldevs(alldevs);

	return 0;
}
