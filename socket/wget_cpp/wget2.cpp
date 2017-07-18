#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "usage: wget <host> <uri>\n";
		exit(1);
	}

	int sockfd = Tcp_connect(argv[1], 80);

	const char *http_get_format = 
		"GET %s HTTP/1.1\r\n"
		"User-Agent: Wget/1.16.3 (linux-gnu)\r\n"
		"Accept: */*\r\n"
		"Accept-Encoding: identity\r\n"
		"Host: %s\r\n"
		"Connection: Keep-Alive\r\n"
		"\r\n";

	char http_get_data[1024];
	sprintf(http_get_data, http_get_format, argv[2], argv[1]);

	// set recv timeout
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof (tv));

	Sendall(sockfd, http_get_data, strlen(http_get_data));

	ofstream ofile;
	string ofile_name = "./index.html";
	ofile.open(ofile_name.c_str());
	if (!ofile) {
		throw runtime_error("open error for "+ofile_name);
	}

	string data;
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

	size_t http_head_pos = data.find(string("\r\n\r\n", 4));
	assert(http_head_pos != string::npos);
	http_head_pos += 4;

	cout << "httpresp:\n"
		<< data.substr(0, http_head_pos)
		<< endl;

	ofile.write(data.c_str()+http_head_pos, data.size()-http_head_pos);
	ofile.flush();
	Close(sockfd);
	ofile.close();

	return 0;
}
