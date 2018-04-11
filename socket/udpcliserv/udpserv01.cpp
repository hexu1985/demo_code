#include "dg_echo.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;
    short servport = 9999;

    if (argc == 2)
        servport = atoi(argv[1]);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(servport);

	Bind(sockfd, (sockaddr *) &servaddr, sizeof(servaddr));

	dg_echo(sockfd, (sockaddr *) &cliaddr, sizeof(cliaddr));
}
