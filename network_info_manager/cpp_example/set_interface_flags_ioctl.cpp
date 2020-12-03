/* set_interface_flags_ioctl.c */

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
#include <unistd.h>

static short get_if_flags(int, struct ifreq*);
static void set_if_flags(int, struct ifreq*);

int main(int argc, char *argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [network interface name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sfd;
    short flags;
    struct ifreq ifr;

    char ifname[IFNAMSIZ] = {'\0'};
    strncpy(ifname, argv[1], IFNAMSIZ-1);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
    flags = get_if_flags(sfd, &ifr);

    ifr.ifr_flags = flags;

    /* set IFF_UP if cleared */
    if (!(flags & IFF_UP)) {
        ifr.ifr_flags |= IFF_UP;
        set_if_flags(sfd, &ifr);
        printf("Interface %s : UP set.\n", ifname);
    }

    flags = ifr.ifr_flags;

    /* clear IFF_PROMISC if set */
    if (flags & IFF_PROMISC) {
        ifr.ifr_flags &= ~IFF_PROMISC;
        set_if_flags(sfd, &ifr);
        printf("Interface %s : PROMISC cleared.\n", ifname);
    }

    close(sfd);

    exit(EXIT_SUCCESS);
}

static short get_if_flags(int s, struct ifreq *ifr)
{
    int ret, saved_errno;
    short if_flags;

    saved_errno = errno;
    ret = ioctl(s, SIOCGIFFLAGS, ifr);
    if (ret == -1 && errno == 19) {
        fprintf(stderr, "Interface %s : No such device.\n", ifr->ifr_name);
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;

    if_flags = ifr->ifr_flags;
    return if_flags;
}

static void set_if_flags(int s, struct ifreq *ifr)
{
    int ret, saved_errno;
    saved_errno = errno;
    ret = ioctl(s, SIOCSIFFLAGS, ifr);
    if (ret == -1) {
        fprintf(stderr, "Interface %s : %s\n", ifr->ifr_name, strerror(errno));
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;
}
