#ifndef __udp_sender_h
#define __udp_sender_h

class UdpSender {
private:
    int sockfd_;

public:
    UdpSender(); 
    ~UdpSender(); 

    void connect(const char *serv_ip, int port);
    int send(const char *buff, int len);
    void close();
};

#endif

