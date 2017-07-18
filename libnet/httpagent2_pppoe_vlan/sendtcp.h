#ifndef __sendtcp_h
#define __sendtcp_h

#include <libnet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ip.h>
#include <netinet/tcp.h>

/*数据包的数据结构的定义*/
struct net_pppoe_hdr
{
	uint8_t type:4;
	uint8_t ver:4;
	uint8_t code;
	uint16_t ssn_id;
	uint16_t length;
	uint16_t protocol;
};

struct net_vlan_hdr
{
	uint16_t id;			//优先级和ID
	uint16_t next_type;	//下一个包的以太网类型
};

bool send_tcp_ack(
		struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_syn_ack(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_data(const char *data, int len,
		struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_rst(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_syn_rst(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_fin(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_fin_ack(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

int build_pppoe_vlan_resp(uint8_t *eth_payload, int buflen,
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num);

void build_tcp_resp(
		struct tcphdr *tcpptr, uint32_t seq, uint32_t ack, uint8_t control, 
		const uint8_t *payload, uint32_t payload_s, libnet_t *l);

void build_ipv4_resp(
		struct iphdr *ipptr, uint16_t ip_len, uint8_t prot,
		const uint8_t *payload, uint32_t payload_s, libnet_t *l);

void build_ethernet_resp(
		struct ether_header *eptr,
		const uint8_t *payload, uint32_t payload_s, libnet_t *l);

#define MAX_SEND_LEN 1400

#endif
