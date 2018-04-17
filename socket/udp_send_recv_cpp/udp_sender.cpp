#include "udp_sender.h"
#include <unistd.h>
#include "wrapsock.h"
#include "wraplib.h"

UdpSender::UdpSender(): sockfd_(-1)
{
	sockfd_ = Socket(AF_INET, SOCK_DGRAM, 0);
}

UdpSender::~UdpSender()
{
    close();
}

void UdpSender::connect(const char *serv_ip, int serv_port)
{
	struct sockaddr_in	servaddr;
	memset(&servaddr, 0x0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);
	Inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);
    Connect(sockfd_, (SA *) &servaddr, sizeof(servaddr));
}

int UdpSender::send(const char *buff, int len)
{
    return ::send(sockfd_, buff, len, 0);
}

void UdpSender::close()
{
    if (sockfd_ >= 0)
        ::close(sockfd_);
}
