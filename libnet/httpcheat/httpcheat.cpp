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

string build_http_200();

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

	const char *filter_host = "www.cplusplus.com";

	if (argc < 2){
		printf("Usage: ipsniffer <interface> [filter host]\n");
		exit(1);
	}

	if (argc >= 3) {
		filter_host = argv[2];
	}

	cout << "filter_host: " << filter_host << endl;

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

	// build http 200 resp
	string http_200_data = build_http_200();

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

		cout << "HTTP host: " << httpget_hdr.host << '\n';
		if (httpget_hdr.host == filter_host) {
			cout << filter_host << endl;
#ifdef SEND_LOCAL
			if (!send_tcp_resp_raw(http_200_data.c_str(), http_200_data.length(),
					tcpptr, ipptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
#else
			if (!send_tcp_resp(http_200_data.c_str(), http_200_data.length(),
					tcpptr, ipptr, eptr, send_descr)) {
				cout << "send_tcp_resp fault!\n";
				exit(1);
			}
#endif
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

// 构造http200报文
string build_http_200()
{
	const char *http_header_template =
		"HTTP/1.0 200 OK\r\n"
		"Date: %s\r\n"
		"Server: nginx\r\n"
		"Content-Length: %d\r\n"
		"Keep-Alive: timeout=2, max=20\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Type: text/html; charset=iso-8859-1\r\n"
		"\r\n";

	const char *http_body_data = 
		"<!DOCTYPE html>\r\n"
		"<html>\r\n"
		"<head>\r\n"
		"<title>this is an fake page!</title>\r\n"
		"<style>\r\n"
		"    body {\r\n"
		"        width: 35em;\r\n"
		"        margin: 0 auto;\r\n"
		"        font-family: Tahoma, Verdana, Arial, sans-serif;\r\n"
		"    }\r\n"
		"</style>\r\n"
		"</head>\r\n"
		"<body>\r\n"
		"<h1>Welcome to fake page!</h1>\r\n"
		"<p>If you see this page, the nginx web server is successfully installed and\r\n"
		"working. Further configuration is required.</p>\r\n"
		"\r\n"
		"<p>For online documentation and support please refer to\r\n"
		"<a href=\"http://nginx.org/\">nginx.org</a>.<br/>\r\n"
		"Commercial support is available at\r\n"
		"<a href=\"http://nginx.com/\">nginx.com</a>.</p>\r\n"
		"\r\n"
		"<p><em>Thank you for using nginx.</em></p>\r\n"
		"</body>\r\n"
		"</html>\r\n"
		"\r\n";

	char http_header_data[1024];
	char http_200_data[2048];

	memset(http_header_data, 0, sizeof(http_header_data));
	memset(http_200_data, 0, sizeof(http_200_data));

	sprintf(http_header_data, http_header_template, 
			get_date_gmt().c_str(), strlen(http_body_data));
	sprintf(http_200_data, "%s%s", http_header_data, http_body_data);

#ifndef NDEBUG
	std::cout << "http_200_data: \n" << http_200_data << std::endl;
#endif

	return http_200_data;
}

