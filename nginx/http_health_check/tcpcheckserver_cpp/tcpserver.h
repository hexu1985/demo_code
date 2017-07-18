#ifndef __unp_tcpserver_h
#define __unp_tcpserver_h

#include <string>
#include <memory>

class TcpConnectionHandler {
public:
    // 当有新连接接入, 会调用该方法,
    // 如果该方法返回false, sockfd将被close,
    // 否则sockfd将加入到handler map中.
    virtual bool setup(int sockfd) = 0;

    // 当有数据进入时, 会调用该方法,
    // 如果该方法返回false, sockfd将被close, 并且将sockfd从handler map中删除,
    virtual bool handle(int sockfd) = 0;

    // 当sockfd已经被setup成功后, sockfd被close时调用
    virtual void finish(int sockfd) = 0;
};


// TcpServer非线程安全
class TcpServer {
public:
    TcpServer();
    ~TcpServer();

    // 以下四种操作必须在TcpServer的stoped(即!is_running())状态下才行
    void add_handler(const std::string &listen_host, int listen_port, std::shared_ptr<TcpConnectionHandler> handler);
    std::shared_ptr<TcpConnectionHandler> find_handler(const std::string &listen_host, int listen_port);
    void remove_handler(const std::string &listen_host, int listen_port);
    void clear_all_handlers();

    bool is_running();
    void start();
    void stop();
 
private:
    class Impl;
    Impl *impl_;
};

#endif
