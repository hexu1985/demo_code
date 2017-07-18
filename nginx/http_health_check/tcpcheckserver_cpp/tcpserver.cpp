#include "tcpserver.h"

#include <set>
#include <map>
#include <unordered_map>
#include <tuple>
#include <thread>
#include <cassert>

#include "wrapunix.h"
#include "wrapsock.h"
#include "tcp_listen.h"
#include "sock_ntop.h"

class TcpServer::Impl {
private:
    typedef std::tuple<std::string, int> addr_type;
    typedef std::map<addr_type, std::shared_ptr<TcpConnectionHandler>> addr2handler_map_type;
    addr2handler_map_type addr2handler_map_;        // map: listen_addr -> handler
    std::shared_ptr<std::thread> epoll_thread_;     // thread of run select loop
    int thread_ctl_pipe_[2];                        // notify cancel to thread

    const char *THREAD_CTL_CANCEL = "CANCEL";

public:
    Impl()
    {
        Socketpair(AF_LOCAL, SOCK_DGRAM, 0, thread_ctl_pipe_);
    }

    ~Impl()
    {
        stop();
        close(thread_ctl_pipe_[0]);
        close(thread_ctl_pipe_[1]);
    }

    void add_handler(const std::string &listen_host, int listen_port, std::shared_ptr<TcpConnectionHandler> handler)
    {
        assert(!is_running());
        auto listen_addr = addr_type(listen_host, listen_port);
        addr2handler_map_[listen_addr] = handler;
    }

    void remove_handler(const std::string &listen_host, int listen_port)
    {
        assert(!is_running());

        auto listen_addr = addr_type(listen_host, listen_port);
        addr2handler_map_.erase(listen_addr);
    }

    std::shared_ptr<TcpConnectionHandler> find_handler(const std::string &listen_host, int listen_port)
    {
        assert(!is_running());

        auto listen_addr = addr_type(listen_host, listen_port);
        if (addr2handler_map_.count(listen_addr)) {
            // no handler found
            return std::shared_ptr<TcpConnectionHandler>();
        }
        return addr2handler_map_[listen_addr];
    }

    void clear_all_handlers()
    {
        assert(!is_running());

        addr2handler_map_.clear();
    }
 
    bool is_running()
    {
        return epoll_thread_ != nullptr;
    }

    void start()
    {
        if (is_running()) {
            return;
        }

        epoll_thread_.reset(new std::thread(&TcpServer::Impl::epoll_routine, this));
    }

    void stop()
    {
        if (!is_running()) {
            return;
        }

        notify_cancel_thread();
        epoll_thread_->join();
        epoll_thread_.reset();
    }

private:
    void notify_cancel_thread()
    {
        Write(thread_ctl_pipe_[1], (void *) THREAD_CTL_CANCEL, strlen(THREAD_CTL_CANCEL));
    }

    bool is_recv_cancel()
    {
        char buf[128];
        auto n = read(thread_ctl_pipe_[0], buf, sizeof(buf)); 
        if (n == (int) strlen(THREAD_CTL_CANCEL) && memcmp(buf, THREAD_CTL_CANCEL, n) == 0)
            return true;
        else
            return false;
    }

    typedef std::unordered_map<int, std::shared_ptr<TcpConnectionHandler>> fd2handler_map_type;

    void init_listenfds(std::set<int> &listenfds, fd2handler_map_type &fd2handler_map)
    {
        listenfds.clear();
        fd2handler_map.clear();

        for (auto &item : addr2handler_map_) {
            addr_type addr = item.first;
            auto handler = item.second;

            std::string listen_host;
            int listen_port;
            std::tie(listen_host, listen_port) = addr;

            auto listenfd = Tcp_listen(listen_host.empty() ? NULL : listen_host.c_str(), std::to_string(listen_port).c_str(), NULL);

            listenfds.insert(listenfd);
            fd2handler_map[listenfd] = handler;
        }
    }

    void add_fd_events_to_epoll(int epfd, int fd, uint32_t events)
    {
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = events;
        Epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    }

    void remove_fd_from_epoll(int epfd, int fd)
    {
        Epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    } 

    void init_epoll(int epfd, const std::set<int> &listenfds)
    {
        add_fd_events_to_epoll(epfd, thread_ctl_pipe_[0], EPOLLIN);

        for (auto fd : listenfds) {
            add_fd_events_to_epoll(epfd, fd, EPOLLIN);
        }
    }

    void print_epoll_event(struct epoll_event &ev)
    {
        printf(" fd=%d; events: %s%s%s%s%s\n", ev.data.fd,
                (ev.events & EPOLLIN) ? "EPOLLIN " : "",
                (ev.events & EPOLLOUT) ? "EPOLLOUT " : "",
                (ev.events & EPOLLRDHUP) ? "EPOLLRDHUP " : "",
                (ev.events & EPOLLHUP) ? "EPOLLHUP " : "",
                (ev.events & EPOLLERR) ? "EPOLLERR " : "");
    }

    void close_all_fds(int epfd, const std::set<int> &listenfds, const fd2handler_map_type &fd2handler_map)
    {
        for (auto item : fd2handler_map) {
            auto fd = item.first;
            auto handler = item.second;
            if (!listenfds.count(fd)) {
                handler->finish(fd);
            }
            close(fd);
        }
        close(epfd);
    }

    void epoll_routine()
    {
        std::set<int> listenfds;
        fd2handler_map_type fd2handler_map;
        init_listenfds(listenfds, fd2handler_map);

        const int MAX_EVENTS = 5;
        struct epoll_event evlist[MAX_EVENTS];

        int epfd = Epoll_create(MAX_EVENTS);
        init_epoll(epfd, listenfds);

        for ( ; ; ) {
            printf("%s, epoll_wait\n", __func__);
            auto nready = Epoll_wait(epfd, evlist, MAX_EVENTS, -1);

            for (int i = 0; i < nready; ++i) {
                print_epoll_event(evlist[i]);

                auto fd = evlist[i].data.fd;
                auto events = evlist[i].events;

                if (fd == thread_ctl_pipe_[0] && events & EPOLLIN) {    // 线程控制管道
                    if (is_recv_cancel()) {
                        close_all_fds(epfd, listenfds, fd2handler_map);
                        return;
                    }

                    continue;
                }

                if (listenfds.count(fd) && events & EPOLLIN) {  // 新连接接入
                    struct sockaddr_storage cliaddr;
                    socklen_t clilen = sizeof(cliaddr);
                    auto sockfd = Accept(fd, (SA *) &cliaddr, &clilen);
                    printf("new client: %s\n", Sock_ntop((struct sockaddr *) &cliaddr, clilen));

                    auto handler = fd2handler_map[fd];
                    if (handler->setup(sockfd)) {
                        fd2handler_map[sockfd] = handler;
                        add_fd_events_to_epoll(epfd, sockfd, EPOLLIN | EPOLLRDHUP);
                    } else {
                        close(sockfd);
                    }

                    continue;
                }

                if (events & (EPOLLIN | EPOLLRDHUP)) {  // 已连接有数据
                    auto handler = fd2handler_map[fd];

                    if (events & EPOLLRDHUP || !handler->handle(fd)) {
                        handler->finish(fd);
                        remove_fd_from_epoll(epfd, fd);
                        fd2handler_map.erase(fd);
                    }

                    continue;
                }
            }
        }
    }
};

TcpServer::TcpServer()
{
    impl_ = new TcpServer::Impl();
}

TcpServer::~TcpServer()
{
    delete impl_;
}

void TcpServer::add_handler(const std::string &listen_host, int listen_port, std::shared_ptr<TcpConnectionHandler> handler)
{
    return impl_->add_handler(listen_host, listen_port, handler);
}

std::shared_ptr<TcpConnectionHandler> TcpServer::find_handler(const std::string &listen_host, int listen_port)
{
    return impl_->find_handler(listen_host, listen_port);
}

void TcpServer::remove_handler(const std::string &listen_host, int listen_port)
{
    return impl_->remove_handler(listen_host, listen_port);
}

void TcpServer::clear_all_handlers()
{
    return impl_->clear_all_handlers();
}

bool TcpServer::is_running()
{
    return impl_->is_running();
}

void TcpServer::start()
{
    return impl_->start();
}

void TcpServer::stop()
{
    return impl_->stop();
}
 
