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

#include "httpresp.h"
#include "wget.h"

using namespace std;
using namespace std::tr1;

namespace {

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

}	// namespace

#define MAX_LEN_PER_RECV 8192

shared_ptr<string> wget_local(const char *httpget, int httpget_len)
{
	static struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	servaddr.sin_port = htons(80);

	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	Socket_guard auto_close(sockfd);

	Connect(sockfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

	// set recv timeout
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof (tv));

	// send http request
	Sendall(sockfd, httpget, httpget_len);

	// 读取http response head
	shared_ptr<string> httpresp(new string);
	string &data = *httpresp;
	char buf[MAX_LEN_PER_RECV];
	data.reserve(MAX_LEN_PER_RECV);
	size_t http_head_end = string::npos; 
	while (true) {
		int n = recv(sockfd, buf, sizeof (buf), 0);
		if (n < 0) {
			if (errno == EINTR) {
				continue;
			} else {
				throw runtime_error("recv error: "+string(strerror(errno)));
			}
		} else if (n == 0) {
			break;
		} else {
			data.append(buf, n);
			http_head_end = data.find(string("\r\n\r\n", 4));
			if (http_head_end != string::npos)
				break;
		}
	}
	http_head_end += 4;

	// 解析http response head, 并解析出content_length
	Httpresp_header httpresp_hdr;
	if (!httpresp_parse((uint8_t *) data.c_str(), 
				(uint8_t *) data.c_str()+http_head_end, &httpresp_hdr)) {
		throw runtime_error("httpresp_parse error!");
	}

	// 读取content
	if (!httpresp_hdr.content_length.empty()) {
		int nleft = atoi(httpresp_hdr.content_length.c_str());
		nleft -= (data.size()-http_head_end);
		data.reserve(data.size()+nleft);
		while (nleft > 0) {
			int n = recv(sockfd, buf, std::min<int>(sizeof (buf), nleft), 0);
			if (n < 0) {
				if (errno == EINTR) {
					continue;
				} else {
					throw runtime_error("recv error: "+string(strerror(errno)));
				}
			} else if (n == 0) {
				break;
			} else {
				data.append(buf, n);
				nleft -= n;
			}
		}
	}

	return httpresp;
}
