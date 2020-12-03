/* get_interface_flags_ioctl.c */

#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <unistd.h>

static int get_netcard_type(int, char *);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [network interface name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sfd;
    int type;
    char ifname[IFNAMSIZ] = {'\0'};
    strncpy(ifname, argv[1], IFNAMSIZ-1);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    type = get_netcard_type(sfd, ifname);

    printf("Interface %s : ", ifname);
    switch(type) {
        case ARPHRD_NETROM:
            printf("ARPHRD_NETROM");
            break;
        case ARPHRD_ETHER:
            printf("ARPHRD_ETHER");
            break;
        case ARPHRD_PPP:
            printf("ARPHRD_PPP");
            break;
        case ARPHRD_EETHER:
            printf("ARPHRD_EETHER");
            break;
        case ARPHRD_IEEE802:
            printf("ARPHRD_IEEE802");
            break;
        default:
            printf("UNKNOWN");
            break;
    }

    printf("\n");

    close(sfd);
    exit(EXIT_SUCCESS);
}

static int get_netcard_type(int s, char *dev)
{
    int saved_errno, ret;
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    saved_errno = errno;
    ret = ioctl(s, SIOCGIFHWADDR, &ifr);
    if (ret == -1 && errno == 19) {
        fprintf(stderr, "Interface %s : No such device.\n", dev);
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;

    return ifr.ifr_hwaddr.sa_family;
}
