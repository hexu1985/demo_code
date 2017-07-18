/* include fig01 */
#include <iostream>
#include <string>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define MAXLINE     4096    /* max text line length */

int Socket(int family, int type, int protocol)
{
	int sockfd;

	if ((sockfd = socket(family, type, protocol)) < 0) {
		throw runtime_error("socket error: "+string(strerror(errno)));
	}
	return sockfd;
}

void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
	if (bind(sockfd, myaddr, addrlen) < 0) {
		throw runtime_error("bind error: "+string(strerror(errno)));
	}
}

void Listen(int sockfd, int backlog)
{
	if (listen(sockfd, backlog) < 0) {
		throw runtime_error("listen error: "+string(strerror(errno)));
	}
}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int n;

again:
	if ((n = accept(sockfd, cliaddr, addrlen)) < 0) {
#ifdef EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			throw runtime_error("accept error: "+string(strerror(errno)));
	}
	return n;
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout)
{
	int n;
	
	if ((n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0) {
		throw runtime_error("select error: "+string(strerror(errno)));
	}
	return(n);      /* can return 0 on timeout */
}

void Close(int sockfd)
{
	if (close(sockfd) == -1) {
		throw runtime_error("close error: "+string(strerror(errno)));
	}
}

ssize_t writen(int sockfd, const void *buff, size_t nbytes)
{
	size_t nleft = nbytes;
	ssize_t nwritten = 0;
	const char *ptr = (const char *) buff;

	while (nleft > 0) {
		if ((nwritten = write(sockfd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;	// again call write again
			else
				return -1;
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return nbytes;
}

void Writen(int sockfd, const void *buff, size_t nbytes)
{
	if (writen(sockfd, buff, nbytes) != (ssize_t) nbytes) {
		throw runtime_error("writen error: "+string(strerror(errno)));
	}
}

int
main(int argc, char **argv)
{
	int					i, maxi, maxfd, listenfd, connfd, sockfd;
	int					nready, client[FD_SETSIZE];
	ssize_t				n;
	fd_set				rset, allset;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(9999);

	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

	Listen(listenfd, 5);

	maxfd = listenfd;			/* initialize */
	maxi = -1;					/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;			/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
		rset = allset;		/* structure assignment */
		nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
			cout << "new client: ("
				<< inet_ntoa(cliaddr.sin_addr) << ", "
				<< ntohs(cliaddr.sin_port) << ") connected" 
				<< endl;

			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE) {
				throw runtime_error("too many clients");
			}

			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				if ( (n = read(sockfd, buf, MAXLINE)) < 0) {
					throw runtime_error("read error: "+string(strerror(errno)));
				} else if (n == 0) {
					cout << "client: ("
						<< inet_ntoa(cliaddr.sin_addr) << ", "
						<< ntohs(cliaddr.sin_port) << ") closed connection" 
						<< endl;
					/*4connection closed by client */
					Close(sockfd);

					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else {
					Writen(sockfd, buf, n);
				}

				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}
/* end fig02 */
