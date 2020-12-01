/* list_network_interfaces_ioctl.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int sfd, if_count, i;
    struct ifconf ifc;
    struct ifreq ifr[10];
    char ipaddr[INET_ADDRSTRLEN] = {'\0'};

    memset(&ifc, 0, sizeof(struct ifconf));

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    ifc.ifc_len = 10 * sizeof(struct ifreq);
    ifc.ifc_buf = (char *)ifr;

    /* SIOCGIFCONF is IP specific. see netdevice(7) */
    ioctl(sfd, SIOCGIFCONF, (char *)&ifc);

    if_count = ifc.ifc_len / (sizeof(struct ifreq));
    for (i = 0; i < if_count; i++) {
        printf("Interface %s : ", ifr[i].ifr_name);    
        inet_ntop(AF_INET, 
        &(((struct sockaddr_in *)&(ifr[i].ifr_addr))->sin_addr),
        ipaddr, INET_ADDRSTRLEN);
        printf("%s\n", ipaddr);
    }
    
    close(sfd);

    exit(EXIT_SUCCESS);
}
