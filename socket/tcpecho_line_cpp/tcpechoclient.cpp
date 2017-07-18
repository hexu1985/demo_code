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

ssize_t recvline(int sockfd, std::string &data, const std::string &end_tag)
{
    char buf[2048];
    int nrecv;

    data.clear();
	while (true) {
		if ((nrecv = recv(sockfd, buf, sizeof(buf), 0)) < 0) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		} else if (nrecv == 0)
			break;		// EOF

        data.append(buf, nrecv);
        if (data.length() >= end_tag.length() 
                && data.compare(data.length()-end_tag.length(), end_tag.length(), end_tag) == 0)
            break;
	}
	return data.length();
}

ssize_t Recvline(int sockfd, std::string &data, const std::string &end_tag)
{
	ssize_t n;
	if ((n = recvline(sockfd, data, end_tag)) < 0)
		throw runtime_error("recvline error: "+string(strerror(errno)));
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
    string buf;
	while (getline(cin, data)) {
        data += "\r\n";
		Sendall(sockfd, data.data(), data.size());
		int n = Recvline(sockfd, buf, "\r\n");
		if (n == 0) {
			throw runtime_error("server terminated prematurely");
		}
		cout << "Received: " << buf << endl;
	}

	Close(sockfd);

	return 0;
}
