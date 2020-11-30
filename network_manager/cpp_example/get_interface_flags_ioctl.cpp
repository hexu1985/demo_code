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

static short get_if_flags(int, char *);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [network interface name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sfd;
    short flags;
    char ifname[IFNAMSIZ] = {'\0'};
    strncpy(ifname, argv[1], IFNAMSIZ-1);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    flags = get_if_flags(sfd, ifname);

    printf("Interface %s : ", ifname);
    if (flags & IFF_UP)
        printf("UP ");

    if (flags & IFF_RUNNING)
        printf("RUNNING ");

    if (flags & IFF_LOOPBACK)
        printf("LOOPBACK ");

    if (flags & IFF_BROADCAST)
        printf("BROADCAST ");

    if (flags & IFF_MULTICAST)
        printf("MULTICAST ");

    if (flags & IFF_PROMISC)
        printf("PROMISC");

#ifndef IFF_LOWER_UP
#define IFF_LOWER_UP 0x10000
    if (flags & IFF_LOWER_UP)
        printf("LOWER_UP");
#endif

    printf("\n");

    close(sfd);
    exit(EXIT_SUCCESS);
}

static short get_if_flags(int s, char *dev)
{
    int saved_errno, ret;
    short if_flags;
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    saved_errno = errno;
    ret = ioctl(s, SIOCGIFFLAGS, &ifr);
    if (ret == -1 && errno == 19) {
        fprintf(stderr, "Interface %s : No such device.\n", dev);
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;
    if_flags = ifr.ifr_flags;

    return if_flags;
}
