#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "error.h"
#include "sock_ntop.h"

void nslookup_v4(const char *host)
{
	int n;
	struct addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;

	if ( (n = getaddrinfo(host, NULL, &hints, &res)) != 0)
		err_quit("tcp_connect error for %s: %s", host, gai_strerror(n));
	ressave = res;

	do {
        /* canonname should be set only in first addrinfo{} */
        if (hints.ai_flags & AI_CANONNAME) {
            if (res->ai_canonname)
                printf(", ai_canonname = %s", res->ai_canonname);
        }
        printf("\n");

        printf("\taddress: %s\n",
                Sock_ntop(res->ai_addr, res->ai_addrlen));

	} while ( (res = res->ai_next) != NULL);

	freeaddrinfo(ressave);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || (argc >= 2 && argv[1][0] == '-')) {
        printf("usage: nslookup_v4 host\n");
        exit(1);
    }

    nslookup_v4(argv[1]);

    return 0;
}

