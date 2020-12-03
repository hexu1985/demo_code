/* get_interface_ip_address_ioctl.c */

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

static char *get_ipaddr(const char *);

int main(int argc, char *argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [network interface name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char ifname[IFNAMSIZ] = {'\0'};
    strncpy(ifname, argv[1], IFNAMSIZ-1);

    char *ip = get_ipaddr(ifname);

    printf("Interface %s : %s\n", ifname, ip);
    
    return 0;
}

static char *get_ipaddr(const char *dev)
{
    int sfd, saved_errno, ret;
    struct ifreq ifr;
    char *ipaddr;

    ipaddr = (char *)malloc(INET_ADDRSTRLEN);
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    errno = saved_errno;
    ret = ioctl(sfd, SIOCGIFADDR, &ifr);
    if (ret == -1) {
        if (errno == 19) {
            fprintf(stderr, "Interface %s : No such device.\n", dev);
            exit(EXIT_FAILURE);
        }
        if (errno == 99) {
            fprintf(stderr, "Interface %s : No IPv4 address assigned.\n", dev);
            exit(EXIT_FAILURE);
        }
    }
    saved_errno = errno;

    inet_ntop(AF_INET, &(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr), ipaddr, INET_ADDRSTRLEN);
    
    close(sfd);
    return ipaddr;
}
