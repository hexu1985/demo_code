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

void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	if (connect(sockfd, servaddr, addrlen) < 0) {
		throw runtime_error("connect error: "+string(strerror(errno)));
	}
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

ssize_t recvall(int sockfd, void *buff, size_t nbytes)
{
	size_t nleft = nbytes;
	ssize_t nrecv = 0;
	char *ptr = (char *) buff;

	while (nleft > 0) {
		if ((nrecv = recv(sockfd, ptr, nleft, 0)) < 0) {
			if (errno == EINTR)
				nrecv = 0;	// call recv again
			else
				return -1;
		} else if (nrecv == 0)
			break;		// EOF

		nleft -= nrecv;
		ptr += nrecv;
	}
	return (nbytes - nleft);
}

ssize_t Recvall(int sockfd, void *buff, size_t nbytes)
{
	ssize_t n;
	if ((n = recvall(sockfd, buff, nbytes)) < 0)
		throw runtime_error("recvall error: "+string(strerror(errno)));
	return n;
}

void Close(int sockfd)
{
	if (close(sockfd) == -1) {
		throw runtime_error("close error: "+string(strerror(errno)));
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "usage: tcpcli <IPaddress> <Port>\n";
		exit(1);
	}
	string host = argv[1];
	uint16_t port = atoi(argv[2]);

#ifndef	NDEBUG
	cerr << "argv[1]: " << argv[1] << '\n';
	cerr << "argv[2]: " << argv[2] << '\n';
	cerr << "host: " << host << '\n';
	cerr << "port: " << port << '\n';
#endif

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;						// IPv4
	servaddr.sin_addr.s_addr = Inet_addr(host.c_str());	// IPv4 address
	servaddr.sin_port = htons(port);					// port

	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	Connect(sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

	string data;
	char buf[2048];
	while (getline(cin, data)) {
		Sendall(sockfd, data.data(), data.size());
		int n = Recvall(sockfd, buf, data.size());
		if (n == 0) {
			throw runtime_error("server terminated prematurely");
		}
		assert(n < 2048);
		buf[n] = '\0';
		cout << "Received: " << buf << endl;
	}

	Close(sockfd);

	return 0;
}
