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

in_addr_t Inet_addr(const char *str)
{
	in_addr_t addr = inet_addr(str);
	if (addr == INADDR_NONE)
		throw runtime_error("inet_addr error: "+string(str));
	return addr;
}

int Socket(int family, int type, int protocol)
{
	int sockfd;

	if ((sockfd = socket(family, type, protocol)) < 0) {
		throw runtime_error("socket error: "+string(strerror(errno)));
	}
	return sockfd;
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(sockfd, level, optname, optval, optlen) < 0) {
		throw runtime_error("setsockopt error: "+string(strerror(errno)));
	}
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

ssize_t sendall(int sockfd, const void *buff, size_t nbytes)
{
	size_t nleft = nbytes;
	ssize_t nsend = 0;
	const char *ptr = (const char *) buff;

	while (nleft > 0) {
		if ((nsend = send(sockfd, ptr, nleft, 0)) <= 0) {
			if (nsend < 0 && errno == EINTR)
				nsend = 0;	// again call send again
			else
				return -1;
		}

		nleft -= nsend;
		ptr += nsend;
	}
	return nbytes;
}

void Sendall(int sockfd, const void *buff, size_t nbytes)
{
	if (sendall(sockfd, buff, nbytes) != (ssize_t) nbytes) {
		throw runtime_error("sendall error: "+string(strerror(errno)));
	}
}

void Close(int sockfd)
{
	if (close(sockfd) == -1) {
		throw runtime_error("close error: "+string(strerror(errno)));
	}
}

pid_t Fork()
{
	pid_t pid;
	if ((pid = fork()) == -1) {
		throw runtime_error("fork error: "+string(strerror(errno)));
	}

	return pid;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;					// IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	// IPv4 address
	servaddr.sin_port = htons(9999);				// port

	int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	const int on = 1;
	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));

	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

	Listen(listenfd, 5);

	struct sockaddr_in cliaddr;
	socklen_t clilen;
	int connfd;
	pid_t childpid;
	ssize_t n;
	char buf[8192];
	while (true) {
		clilen = sizeof (cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		cout << "new client: ("
			<< inet_ntoa(cliaddr.sin_addr) << ", "
			<< ntohs(cliaddr.sin_port) << ") connected" 
			<< endl;

		if ((childpid = Fork()) == 0) { // child process
			Close(listenfd);	// close listening socket

again:
			// process the request
			while ((n = recv(connfd, buf, sizeof (buf), 0)) > 0) {
				Sendall(connfd, buf, n);
			}

			if (n < 0 && errno == EINTR)
				goto again;
			else if (n < 0)
				throw runtime_error("recv error: "+string(strerror(errno)));

			cout << "client: ("
				<< inet_ntoa(cliaddr.sin_addr) << ", "
				<< ntohs(cliaddr.sin_port) << ") closed connection" 
				<< endl;

			exit(0);
		}
		Close(connfd);	// parent closes connected socket
	}

	return 0;
}

