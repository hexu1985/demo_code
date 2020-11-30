/* get_interface_mac_address_ioctl.c */

#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>

static unsigned char *get_if_mac(const char *);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [network interface name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char ifname[IFNAMSIZ] = {'\0'};
    strncpy(ifname, argv[1], IFNAMSIZ-1);

    unsigned char *mac = get_if_mac(ifname);
    
    printf("Interface %s : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
    ifname, *mac, *(mac+1), *(mac+2), *(mac+3), *(mac+4), *(mac+5));

    return 0;
}

static unsigned char *get_if_mac(const char *dev)
{
    int sfd, ret, saved_errno, i;
    unsigned char *mac_addr;
    struct ifreq ifr;

    mac_addr = (unsigned char *)malloc(ETH_ALEN);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    saved_errno = errno;
    ret = ioctl(sfd, SIOCGIFHWADDR, &ifr);
    if (ret == -1 && errno == 19) {
        fprintf(stderr, "Interface %s : No such device.\n", dev);
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;

    if (ifr.ifr_addr.sa_family == ARPHRD_LOOPBACK) {
        printf("Interface %s : A Loopback device.\n", dev);
        printf("MAC address is always 00:00:00:00:00:00\n");
        exit(EXIT_SUCCESS);
    }

    if (ifr.ifr_addr.sa_family != ARPHRD_ETHER) {
        fprintf(stderr, "Interface %s : Not an Ethernet device.\n", dev);
        exit(EXIT_FAILURE);
    }

    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);

    return (unsigned char *)mac_addr;
}
