#include <stdio.h>
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

int main()
{
	int num = sizeof(dlt_descriptions) / sizeof(dlt_descriptions[0]);
	for (int i = 0; i < num; i++) {
		printf("datalink type[%d]: %s\n", 
				dlt_descriptions[i].dlt_type, dlt_descriptions[i].dlt_desc);
	}
}

