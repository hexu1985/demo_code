#include "wget.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;
using namespace std::tr1;

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

struct hostent *Gethostbyname(const char *hostname)
{
	struct hostent *hptr;
	if ((hptr = gethostbyname(hostname)) == NULL) {
		throw runtime_error("gethostbyname error for "+string(hostname)+": "+
				string(hstrerror(h_errno)));
	}
	return hptr;
}

void Close(int sockfd)
{
	if (close(sockfd) == -1) {
		throw runtime_error("close error: "+string(strerror(errno)));
	}
}

int Tcp_connect(const char *host, int port)
{
	struct hostent *hptr = Gethostbyname(host);
	if (hptr->h_addrtype != AF_INET) {
		throw runtime_error("only support ipv4!");
	}

	char **pptr = hptr->h_addr_list;
	for ( ; *pptr != NULL; pptr++) {
		struct sockaddr_in servaddr;
		memset(&servaddr, 0, sizeof (servaddr));
		servaddr.sin_family = AF_INET;						// IPv4
		servaddr.sin_addr = *((struct in_addr *) *pptr);	// IPv4 address
		servaddr.sin_port = htons(80);						// port

		int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
		
		try {
			Connect(sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr));
			cout << "connect to " << inet_ntoa(servaddr.sin_addr) 
				<< " ok" << endl;
			return sockfd;
		} catch (const runtime_error &e) {
			cerr << e.what() << '\n';
		}

		Close(sockfd);
	}

	ostringstream os;
	os << "tcp_connect error for " << host << ", " << port;
	throw runtime_error(os.str());
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

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(sockfd, level, optname, optval, optlen) < 0) {
		throw runtime_error("setsockopt error: "+string(strerror(errno)));
	}
}

class Socket_guard {
	int sockfd_;
public:
	Socket_guard(int sockfd): sockfd_(sockfd) {}
	~Socket_guard() { close(sockfd_); }
};

shared_ptr<string> wget(const char *httpget, int httpget_len,
		const char *server_host, uint16_t port)
{
	int sockfd = Tcp_connect(server_host, port);

	Socket_guard auto_close(sockfd);

	// set recv timeout
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof (tv));

	shared_ptr<string> httpresp(new string);
	string &data = *httpresp;

	Sendall(sockfd, httpget, httpget_len);

	char buf[8192];

	while (true) {
		int n = recv(sockfd, buf, sizeof (buf), 0);
		if (n < 0) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EWOULDBLOCK) {
				cerr << "recv time out!\n";
				break;
			} else {
				throw runtime_error("recv error: "+string(strerror(errno)));
			}
		} else if (n == 0) {
			break;
		} else {
			data.append(buf, n);
		}
	}

	return httpresp;
}
