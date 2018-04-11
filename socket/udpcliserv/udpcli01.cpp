#include <stdlib.h>
#include "dg_cli.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
    short servport = 9999;

	if (argc < 2)
		err_quit("usage: udpcli <IPaddress> [Port]");

    if (argc == 3)
        servport = atoi(argv[2]);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(servport);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (sockaddr *) &servaddr, sizeof(servaddr));

	exit(0);
}
