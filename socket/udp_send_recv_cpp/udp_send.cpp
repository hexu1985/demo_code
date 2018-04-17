#include <iostream>
#include <string>
#include <stdlib.h>
#include "wrapsock.h"
#include "wraplib.h"

using namespace std;

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 3)
		err_quit("usage: udpcli <IPaddress> <port>");

    char *serv_host = argv[1];
    short serv_port = atoi(argv[2]);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);
	Inet_pton(AF_INET, serv_host, &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    string str;
    while (getline(cin, str)) //循环读取数据
    {
        send(sockfd, str.c_str(), str.length(), 0);
    }

	exit(0);
}
