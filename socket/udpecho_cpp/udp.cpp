#include <iostream>
#include <string>
#include <stdexcept>

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

void Getline(istream &in, string &str)
{
	if (!getline(in, str)) {
		throw runtime_error("getline error");
	}
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
		cerr << "usage: udpcli <IPaddress> <Port>\n";
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

	int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	cout << "Enter data to transmit: \n";
	string data;
	Getline(cin, data);
	Sendto(sockfd, data.data(), data.size(), 0, 
			(struct sockaddr *) &servaddr, sizeof (servaddr));

	cout << "Looking for replies; press Ctrl-C or Ctrl-Break to stop.\n";
	char buf[2048];
	while (true) {
		int n = Recvfrom(sockfd, buf, sizeof (buf), 0, NULL, NULL);
		if (n == 0)
			break;
		assert(n < 2048);
		buf[n] = '\0';
		cout << "Received: " << buf << endl;
	}

	Close(sockfd);

	return 0;
}
