/* change_ifname_ioctl.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

static void change_ifname(char *, char *);
static void shutdown_if_up(char *);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "%s [old ifname] [new ifname]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char old_ifname[IFNAMSIZ] = {'\0'};
    strncpy(old_ifname, argv[1], IFNAMSIZ);

    char new_ifname[IFNAMSIZ] = {'\0'};
    strncpy(new_ifname, argv[2], IFNAMSIZ);

    change_ifname(old_ifname, new_ifname);
    printf("Interface name %s has been changed to %s\n", old_ifname, new_ifname);

    return 0;
}

void change_ifname(char *old_dev, char *new_dev)
{
    int sfd, ret, saved_errno;
    struct ifreq ifr;

    shutdown_if_up(old_dev);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, old_dev, IFNAMSIZ);
    strncpy(ifr.ifr_newname, new_dev, IFNAMSIZ);

    saved_errno = errno;
    ret = ioctl(sfd, SIOCSIFNAME, &ifr);
    if (ret == -1) {
        fprintf(stderr, "Interface %s : %s\n", old_dev, strerror(errno));
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;
}

static void shutdown_if_up(char *dev)
{
    int sfd, ret, saved_errno;
    short flags;
    struct ifreq ifr;

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    saved_errno = errno;
    ret = ioctl(sfd, SIOCGIFFLAGS, &ifr);
    if (ret == -1) {
        fprintf(stderr, "Interface %s : %s\n", dev, strerror(errno));
        exit(EXIT_FAILURE);
    }
    errno = saved_errno;

    flags = ifr.ifr_flags;
    if (flags & IFF_UP) {
        ifr.ifr_flags &= ~IFF_UP;
        saved_errno = errno;
        ret = ioctl(sfd, SIOCSIFFLAGS, &ifr);
        if (ret == -1) {
            fprintf(stderr, "Interface %s : %s\n",dev, strerror(errno));
            exit(EXIT_FAILURE);
        }
        errno = saved_errno;
    }
}

