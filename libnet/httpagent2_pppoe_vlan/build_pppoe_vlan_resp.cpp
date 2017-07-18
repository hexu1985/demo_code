#include "sendtcp.h"
#include <assert.h>

int build_pppoe_vlan_resp(
		uint8_t *eth_payload, 
		int buflen,
		struct net_pppoe_hdr *pppoe, 
		struct net_vlan_hdr *vlan, 
		int vlan_num)
{
	int eth_payload_len = 0;

	// 构造ether
	if (vlan != NULL) {
		assert(buflen <= (vlan_num * sizeof (struct net_vlan_hdr)));

		eth_payload_len = vlan_num * sizeof (struct net_vlan_hdr);
		memcpy(eth_payload, (uint8_t *) vlan, eth_payload_len);
	}

	if (pppoe != NULL) {
		struct net_pppoe_hdr *ppphdr = NULL;
		unsigned short pppoe_payload_len = 0;

		assert(buflen <= eth_payload_len + sizeof (struct net_pppoe_hdr));

		//有PPPOE头的以太数据
		ppphdr = NULL;
		pppoe_payload_len = 0;
		pppoe_payload_len = LIBNET_TCP_H + LIBNET_IPV4_H + 2;

		ppphdr = ( struct net_pppoe_hdr * ) (eth_payload + eth_payload_len);
		ppphdr->ver = 1;
		ppphdr->type = 1;
		ppphdr->code = 0;
		ppphdr->ssn_id = pppoe->ssn_id;
		ppphdr->length = htons (pppoe_payload_len);
		ppphdr->protocol = pppoe->protocol;

		eth_payload_len += sizeof (struct net_pppoe_hdr);
	}

	return eth_payload_len; 
}
