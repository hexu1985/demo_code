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
#include <vector>
#include <string>
#include <iostream>
#include <iterator>

#define BUFSIZE 1024

std::vector<std::string> get_if_name_list(int fd)
{
    std::vector<std::string> if_name_list;
    struct ifconf ifc;
    struct ifreq ifr[10];

    memset(&ifc, 0, sizeof(struct ifconf));
    ifc.ifc_len = 10 * sizeof(struct ifreq);
    ifc.ifc_buf = (char *)ifr;

    /* SIOCGIFCONF is IP specific. see netdevice(7) */
    ioctl(fd, SIOCGIFCONF, (char *)&ifc);

    int if_count = ifc.ifc_len / (sizeof(struct ifreq));
    for (int i = 0; i < if_count; i++) {
        if_name_list.push_back(std::string(ifr[i].ifr_name));
    }
    return if_name_list;
}

int main(int argc, char *argv[])
{
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);

    std::vector<std::string> if_name_list = get_if_name_list(sfd);
    std::cout << "interface list:\n";
    std::ostream_iterator<std::string> out_it (std::cout,"\n");
    std::copy(if_name_list.begin(), if_name_list.end(), out_it);

    close(sfd);

    exit(EXIT_SUCCESS);
}
