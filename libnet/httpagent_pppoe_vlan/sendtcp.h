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

bool send_tcp_ack_syn(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_resp(const char *data, int len,
		struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_fin0(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_fin1(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

bool send_tcp_ack_fin2(struct tcphdr *tcpptr, struct iphdr *ipptr, 
		struct net_pppoe_hdr *pppoe, struct net_vlan_hdr *vlan, int vlan_num,
		struct ether_header *eptr, libnet_t *l);

#define MAX_SEND_LEN 1400

#endif
