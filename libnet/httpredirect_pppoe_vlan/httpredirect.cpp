/* Simple ARP sniffer
 * To compile: gcc tcpsniffer.c -o tcppsniffer -lpcap
 * Run as root!
 * */
#include "httpget.h"
#include "sendtcpresp.h"
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

string build_http_302(const char *url);
string build_http_302_2(const char *url);

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
	struct net_pppoe_hdr *pppoe = NULL;
	struct net_vlan_hdr *vlan = NULL;
	int vlan_num = 0;
	int next_index = 0;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);
	struct in_addr addr;
	libnet_t *send_descr;
	libnet_ptag_t *send_tag;

	if (argc != 4){
		printf("Usage: httpsniffer <interface> <orginal_host> <redirect_url>\n");
		exit(1);
	}
	cout << "interface: " << argv[1] << endl;
	cout << "orginal_host: " << argv[2] << endl;
	cout << "redirect_host: " << argv[3] << endl;

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
        printf("libnet_init() failed: %s", errbuf);
        exit(EXIT_FAILURE);
    }

	// build http 302 resp
	string http_302_data = build_http_302_2(argv[3]);

	// libpcap dev open
	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1,
			0, errbuf);
//	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
//	pcap_compile(descr, &filter, "tcp and dst port 80", 1, mask);
//	pcap_setfilter(descr, &filter);

	Httpget_header httpget_hdr;
	while (1){
		packet = NULL;
		eptr = NULL;
		ipptr = NULL;
		tcpptr = NULL;
		pppoe = NULL;
		vlan = NULL;
		vlan_num = 0;
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

		uint16_t type = ntohs(eptr->ether_type);
		while (type == 0x8100 || type == 0x9100) {
			if (vlan_num == 0) {
				vlan = (struct net_vlan_hdr *) (packet + next_index);
				type = ntohs(vlan->next_type);
			} else {
				struct net_vlan_hdr *tmp_vlan = (struct net_vlan_hdr *) (packet + next_index);
				type = ntohs(tmp_vlan->next_type);
			}
			next_index += sizeof (struct net_vlan_hdr);
			++vlan_num;
		}

		switch (type) {
		case 0x0800:
			ipptr = (struct iphdr *)(packet + next_index);
			next_index += ipptr->ihl*4;
			break;
		case 0x8864:
			pppoe = (net_pppoe_hdr *) (packet + next_index);
			next_index += sizeof (struct net_pppoe_hdr);
			switch (ntohs(pppoe->protocol)) {
			case 0x0021:
				ipptr = (struct iphdr *)(packet + next_index);
				next_index += ipptr->ihl*4;
				break;
			default:
				continue;
			}
			break;
		default:
			continue;
		}

		if (ipptr->protocol != 6)
		   continue;	

		tcpptr = (struct tcphdr *) (packet + next_index);
		next_index += tcpptr->doff*4;

		if (ntohs(tcpptr->dest) != 80)
			continue;

		if (!httpget_unpack((uint8_t *) packet + next_index, 
				(uint8_t *) packet + pkthdr->caplen, &httpget_hdr)) {
			continue;
		}

//		if (httpget_hdr.host == argv[2] && httpget_hdr.uri == "/") {
		if (httpget_hdr.host == argv[2]) {
#ifdef SEND_LOCAL
			if (!send_tcp_resp_raw(http_302_data.c_str(), http_302_data.length(),
					tcpptr, ipptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
#else
			if (!send_tcp_resp_pppoe_vlan(http_302_data.c_str(), 
					http_302_data.length(), tcpptr, ipptr, 
					pppoe, vlan, vlan_num,
					eptr, send_descr)) {
//			if (!send_tcp_resp(http_302_data.c_str(), 
//					http_302_data.length(), tcpptr, ipptr, 
//					eptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
#endif
			cout << "match " << httpget_hdr.host << endl;
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


// 获取当前时间
// 格式如: Mon, 29 Jun 2015 23:24:42 GMT
string get_date_gmt()
{
    time_t t = time(0);
    char timebuf[36] = {0};
    strftime(timebuf, 36, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&t));
    return timebuf;
}

// 构造http302报文
string build_http_302(const char *url)
{
	const char *http_header_template =
		"HTTP/1.0 302 Moved Temporarily\r\n"
		"Date: %s\r\n"
		"Server: nginx\r\n"
		"Location: %s\r\n"
		"Content-Length: %d\r\n"
		"Keep-Alive: timeout=2, max=20\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Type: text/html; charset=iso-8859-1\r\n"
		"\r\n";

	const char *http_body_template = 
		"<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\r\n"
		"<html><head>\r\n"
		"<title>302 Moved Temporarily</title>\r\n"
		"</head><body>\r\n"
		"<h1>Moved Temporarily</h1>\r\n"
		"<p>The document has moved <a href=\"%s\">here</a>.</p>\r\n"
		"</body></html>\r\n"
		"\r\n";

	char http_header_data[1024];
	char http_body_data[1024];
	char http_302_data[2048];

	memset(http_header_data, 0, sizeof(http_header_data));
	memset(http_body_data, 0, sizeof(http_body_data));
	memset(http_302_data, 0, sizeof(http_302_data));

	sprintf(http_body_data, http_body_template, url);
	sprintf(http_header_data, http_header_template, 
			get_date_gmt().c_str(), url, strlen(http_body_data));
	sprintf(http_302_data, "%s%s", http_header_data, http_body_data);

#ifndef NDEBUG
	std::cout << "http_302_data: \n" << http_302_data << std::endl;
#endif

	return http_302_data;
}

// 构造http302报文
string build_http_302_2(const char *url)
{
	const char *http_302_template =
		"HTTP/1.0 302 Found\r\n"
		"Date: %s\r\n"
		"Server: nginx\r\n"
		"Location: %s\r\n"
		"Content-Length: 0\r\n"
		"\r\n";

	char http_302_data[1024];

	memset(http_302_data, 0, sizeof(http_302_data));
	sprintf(http_302_data, http_302_template, get_date_gmt().c_str(), url);

#ifndef NDEBUG
	std::cout << "http_302_data: \n" << http_302_data << std::endl;
#endif

	return http_302_data;
}
