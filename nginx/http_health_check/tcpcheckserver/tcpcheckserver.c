/* include fig01 */
#include	"unp.h"

int
main(int argc, char **argv)
{
	int					maxfd, listenfd, sockfd;
	int					nready;
	fd_set				rset, allset;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr;
#ifdef	NOTDEF
    char                str[INET_ADDRSTRLEN];
#endif

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], NULL);
	else
		err_quit("usage: daytimetcpsrv4 [ <host> ] <service or port>");

	maxfd = listenfd;			/* initialize */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
		rset = allset;		/* structure assignment */
		nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			sockfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef	NOTDEF
			printf("new client: %s, port %d\n",
					Inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
					ntohs(cliaddr.sin_port));
#endif

            Write(sockfd, "X", 1);
            close(sockfd);

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}
	}
}
/* end fig02 */
