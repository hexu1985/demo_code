#include <iostream>
#include <string>
#include <unistd.h>
#include "writen.h"
#include "error.h"
#include "tcp_connect.h"
#include "writen.h"

using namespace std;

void str_cli(istream &in, int sockfd)		/* do it all */
{
    string str;
    while (getline(in, str)) {
        Writen(sockfd, str.data(), str.size());
    }
}

int
main(int argc, char **argv)
{
	int		sockfd;

	if (argc != 3)
		err_quit("usage: tcpcli <hostname> <service>");

	sockfd = Tcp_connect(argv[1], argv[2]);

	str_cli(cin, sockfd);		/* do it all */

    close(sockfd);

    return 0;
}
