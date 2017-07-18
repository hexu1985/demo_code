/* Simple ARP sniffer
 * To compile: gcc tcpsniffer.c -o tcppsniffer -lpcap
 * Run as root!
 * */
#include "sendtcp.h"
#include "wget.h"
#include "httpget.h"
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <libnet.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;
using namespace std::tr1;

#define MAXBYTES2CAPTURE 2048

struct Client_id {
	uint32_t ip;	// network bytes order
	uint16_t port;	// network bytes order
};

struct Http_resp {
	uint32_t beg_seq;			// http_resp begin seqno
	shared_ptr<string> pbuf;	// resp data
};

typedef map<Client_id, Http_resp> Http_resp_map;

bool operator <(const struct Client_id &a, const struct Client_id &b)
{
	return (a.ip < b.ip) || ((a.ip == b.ip) && a.port < b.port);
}

bool operator ==(const struct Client_id &a, const struct Client_id &b) 
{
	return (a.ip == b.ip) && (a.port == b.port);
}

uint32_t get_data_off(struct tcphdr *tcpptr, uint32_t beg_seq)
{
	uint32_t next_seq = ntohl(tcpptr->ack_seq);
	return next_seq - beg_seq;
}

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
	in_addr_t addr;	// network bytes order
	uint16_t port;	// network bytes order
	libnet_t *send_descr;
	libnet_ptag_t *send_tag;
	int next_index = 0;

	if (argc != 4){
		cerr << "Usage: ipsniffer <interface> <ip> <port>\n";
		exit(1);
	}

	addr = inet_addr(argv[2]);
	if (addr == INADDR_NONE) {
		cerr << "invalid ip " << argv[2] << '\n';
		exit(1);
	}

	port = atoi(argv[3]);
	port = ntohs(port);

	// libnet dev open
	send_descr = libnet_init(
            LIBNET_LINK,                            /* injection type */
            argv[1],                                /* network interface */
            errbuf);                                /* error buffer */

    if (send_descr == NULL)
    {
        cerr << "libnet_init() failed: " << errbuf << '\n';
		exit(1);
    }

	// libpcap dev open
	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 1, 0, errbuf);
	pcap_lookupnet(argv[1], &netaddr, &mask, errbuf);
	pcap_compile(descr, &filter, "tcp", 1, mask);
	pcap_setfilter(descr, &filter);

	struct Client_id client_id;
	struct Http_resp http_resp;
	Http_resp_map http_resp_map;
	Httpget_header httpget_hdr;
	while (1){
		packet = NULL;
		eptr = NULL;
		ipptr = NULL;
		tcpptr = NULL;
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

		if (ntohs(eptr->ether_type) != 0x0800)	// only ipv4
			continue;

		ipptr = (struct iphdr *)(packet + next_index);
		next_index += ipptr->ihl*4;

		// filter dest ip
		if (ipptr->daddr != addr)
			continue;

		if (ipptr->protocol != 6)	// only tcp
			continue;	

		tcpptr = (struct tcphdr *) (packet + next_index);
		next_index += tcpptr->doff*4;

		// filter dest port
		if (port != tcpptr->dest)
			continue;

		// get client ip and port
		client_id.ip = ipptr->saddr;
		client_id.port = tcpptr->source;

		// process syn connect handle
		if (tcpptr->syn && !tcpptr->ack) {
			if (!send_tcp_ack_syn(tcpptr, ipptr, eptr, send_descr)) {
				cerr << "send_tcp_ack_syn fault!\n";
				exit(1);
			}
			continue;
		}

		// process fin disconnect handle
		if (tcpptr->fin) {
			if (!send_tcp_ack_fin1(tcpptr, ipptr, eptr, send_descr)) {
				cerr << "send_tcp_ack_fin1 fault!\n";
				exit(1);
			}
			if (!send_tcp_ack_fin2(tcpptr, ipptr, eptr, send_descr)) {
				cerr << "send_tcp_ack_fin2 fault!\n";
				exit(1);
			}
			cerr << "erase from http_resp_map\n";
			http_resp_map.erase(client_id);
			continue;
		}

		// process rst
		if (tcpptr->rst) {
			cerr << "erase from http_resp_map\n";
			http_resp_map.erase(client_id);
			continue;
		}

		if (!tcpptr->ack)
			continue;

		// process http get
		int req_payload_len = ntohs(ipptr->tot_len)-ipptr->ihl*4-tcpptr->doff*4;
		char *req_payload = (char *) (packet + next_index);
		if (req_payload_len != 0) {
			// process psh 
			if (!send_tcp_ack(tcpptr, ipptr, eptr, send_descr)) {
				cerr << "send_tcp_ack_syn fault!\n";
				exit(1);
			}

#ifndef NDEBUG
			// check http get
			if (!httpget_unpack((uint8_t *) req_payload, 
						(uint8_t *) req_payload + req_payload_len,
						&httpget_hdr)) {
				continue;
			}

			cout << "HTTP version: " << httpget_hdr.version << '\n';
			cout << "HTTP method: " << httpget_hdr.method << '\n';
			cout << "HTTP uri: " << httpget_hdr.uri << '\n';
			cout << "HTTP host: " << httpget_hdr.host << '\n';
			cout << "HTTP user_agent: " << httpget_hdr.user_agent << '\n';
			cout << endl;
#endif

			// wget from localhost http server
			http_resp.beg_seq = ntohl(tcpptr->ack_seq);
			http_resp.pbuf = wget(req_payload, req_payload_len, "127.0.0.1", 80);
			http_resp_map.insert(make_pair(client_id, http_resp));
			if (!send_tcp_resp(http_resp.pbuf->data(), 
						std::min<int>(http_resp.pbuf->size(), MAX_SEND_LEN),
						tcpptr, ipptr, eptr, send_descr)) {
				throw runtime_error("send_tcp_resp fault!");
			}
			continue;
		}

		// process ack
		Http_resp_map::const_iterator iter;
		iter = http_resp_map.find(client_id);
		if (iter == http_resp_map.end())
			continue;

		http_resp = iter->second;
		int data_off = get_data_off(tcpptr, http_resp.beg_seq);
		if (!send_tcp_resp(http_resp.pbuf->data() + data_off, 
					std::min<int>(http_resp.pbuf->size() - data_off, 2*MAX_SEND_LEN),
					tcpptr, ipptr, eptr, send_descr)) {
			throw runtime_error("send_tcp_resp fault!");
		}

	}

	return 0;
}

