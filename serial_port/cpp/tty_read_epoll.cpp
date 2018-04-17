#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "wrapunix.h"
#include "wrapsock.h"
#include "wraptermios.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <ttyname1> [ttypname2] [ttyname3] ..." << endl; 
        return 1;
    }

    const int MAX_EVENTS = 5;
    struct epoll_event evlist[MAX_EVENTS];
    int epfd = Epoll_create(MAX_EVENTS);

    std::map<int, std::string> tty_map;

    for (int i = 1; i < argc; i++) {
        int fd = Tty_open_easy(argv[i]);
        cout << "Open tty: " << argv[i] << " ok, " << "fd: " << fd << endl;

        Tty_set_speed(fd, 9600);
        Tty_set_parity(fd, 8, 1, 'N');
        Tty_set_icanon(fd, 0, 0);

        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = EPOLLIN;
        Epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

        tty_map.insert(std::make_pair(fd, std::string(argv[i])));
    }


    int nread;
    const int BUFSIZE = 2048;
    char buff[BUFSIZE];

    string data;
    for ( ; ; ) {
        int nready = Epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        if (nready == 0) {  // timeout
            cerr << ".";
            continue;
        }

        for (int i = 0; i < nready; i++) {
            printf(" fd=%d; tty=%s, events: %s%s%s%s%s\n", 
                    evlist[i].data.fd,
                    tty_map[evlist[i].data.fd].c_str(),
                    (evlist[i].events & EPOLLIN) ? "EPOLLIN " : "",
                    (evlist[i].events & EPOLLOUT) ? "EPOLLOUT " : "",
                    (evlist[i].events & EPOLLRDHUP) ? "EPOLLRDHUP " : "",
                    (evlist[i].events & EPOLLHUP) ? "EPOLLHUP " : "",
                    (evlist[i].events & EPOLLERR) ? "EPOLLERR " : "");

            if (evlist[i].events & POLLERR) {
                cout << "event error of '" << tty_map[evlist[i].data.fd] << "' " << endl;
                tty_map.erase(evlist[i].data.fd);
                Epoll_ctl(epfd, EPOLL_CTL_DEL, evlist[i].data.fd, NULL);
                close(evlist[i].data.fd);
                continue;
            }

            if (evlist[i].events & POLLIN) {
                nread = read(evlist[i].data.fd, buff, BUFSIZE);
                if (nread > 0) {
                    data.assign(buff, nread);
                    cout << "\nread from '" << tty_map[evlist[i].data.fd] << "' " << data.size() << " bytes: " << data << endl;
                } else if (nread == 0) {
                    cout << "no data of '" << tty_map[evlist[i].data.fd] << "' " << endl;
                    tty_map.erase(evlist[i].data.fd);
                    Epoll_ctl(epfd, EPOLL_CTL_DEL, evlist[i].data.fd, NULL);
                    close(evlist[i].data.fd);
                } else {
                    cout << "read error of '" << tty_map[evlist[i].data.fd] << "' " 
                        ": " << strerror(errno) << endl;
                    tty_map.erase(evlist[i].data.fd);
                    Epoll_ctl(epfd, EPOLL_CTL_DEL, evlist[i].data.fd, NULL);
                    close(evlist[i].data.fd);
                }
            } 
        }

        if (tty_map.empty()) {
            cout << "all tty closed!" << endl;
            break;
        }
    }

    close(epfd);

    return 0;
}
