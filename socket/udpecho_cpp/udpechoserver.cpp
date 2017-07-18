#include <iostream>
#include <string>
#include <stdexcept>

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

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

ssize_t Sendto(int sockfd, const void *buff, size_t nbytes, int flags,
		const struct sockaddr *to, socklen_t addrlen)
{
	int nsend;
	if ((nsend = sendto(sockfd, buff, nbytes, flags, to, addrlen)) != (ssize_t) nbytes) {
		throw runtime_error("sendto error: "+string(strerror(errno)));
	}
	return nsend;
}

ssize_t Recvfrom(int sockfd, void *buff, size_t nbytes, int flags,
		struct sockaddr * from, socklen_t *addrlen)
{
	int nrecv;
	if ((nrecv = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0) {
		throw runtime_error("recvfrom error: "+string(strerror(errno)));
	}
	return nrecv;
}

void Close(int sockfd)
{
	if (close(sockfd) == -1) {
		throw runtime_error("close error: "+string(strerror(errno)));
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;					// IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	// IPv4 address
	servaddr.sin_port = htons(9999);				// port

	int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	const int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));

	Bind(sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

	char mesg[8192];
	struct sockaddr_in cliaddr;
	int n;
	socklen_t len;
	while (true) {
		len = sizeof (cliaddr);
		n = Recvfrom(sockfd, mesg, sizeof (mesg), 0, 
				(struct sockaddr *) &cliaddr, &len);
		cout << "Got data from (" 
			<< inet_ntoa(cliaddr.sin_addr) << ", "
			<< ntohs(cliaddr.sin_port) << ")" 
			<< endl;
		Sendto(sockfd, mesg, n, 0, 
				(struct sockaddr *) &cliaddr, len);
	}

	Close(sockfd);

	return 0;
}

