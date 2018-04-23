#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <poll.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "tty_reader.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <ttyname1> [ttypname2] [ttyname3] ..." << endl; 
        return 1;
    }

    std::map<int, std::string> tty_map;
    std::vector<TtyReader *> readers;

    for (int i = 1; i < argc; i++) {
        TtyReader *tty = new TtyReader;
        tty->open(argv[i]);
        cout << "Open tty: " << argv[i] << " ok, " << "fd: " << tty->fileno() << endl;

        tty->setSpeed(9600);
        tty->setParity(8, 1, 'N');
        tty->setIcanon(0, 0);

        readers.push_back(tty);
        tty_map.insert(std::make_pair(tty->fileno(), std::string(argv[i])));
    }

    TtyReader::Poller poller;
    int nread;
    const int BUFSIZE = 2048;
    char buff[BUFSIZE];

    poller.watch(readers);

    string data;
    for ( ; ; ) {
        int nready = poller.poll(-1);
        if (nready == 0) {  // timeout
            cerr << ".";
            continue;
        }

        const std::vector<struct pollfd> &client = poller.getEvents();
        const std::vector<TtyReader *> &ttys = poller.getReaders();

        for (int i = 0; i < client.size(); i++) {
            int tty_fd = client[i].fd;
            if (tty_fd < 0)
                continue;

            TtyReader *tty = ttys[i];
            assert(tty_fd == tty->fileno());

            printf(" fd=%d; tty=%s, events: %s%s%s%s%s\n", 
                    tty_fd,
                    tty_map[tty_fd].c_str(),
                    (client[i].revents & POLLIN) ? "POLLIN " : "",
                    (client[i].revents & POLLOUT) ? "POLLOUT " : "",
                    (client[i].revents & POLLRDHUP) ? "POLLRDHUP " : "",
                    (client[i].revents & POLLHUP) ? "POLLHUP " : "",
                    (client[i].revents & POLLERR) ? "POLLERR " : "");

            if (client[i].revents & POLLERR) {
                cout << "event error of '" << tty_map[tty_fd] << "' " << endl;
                tty_map.erase(tty_fd);
                poller.unwatch(tty);
                tty->close();
                continue;
            }

            if (client[i].revents & POLLIN) {
                nread = tty->read(buff, BUFSIZE);
                if (nread > 0) {
                    data.assign(buff, nread);
                    cout << "\nread from '" << tty_map[tty_fd] << "' " << data.size() << " bytes: " << data << endl;
                } else if (nread == 0) {
                    cout << "no data of '" << tty_map[tty_fd] << "' " << endl;
                    tty_map.erase(tty_fd);
                    poller.unwatch(tty);
                    tty->close();
                } else {
                    cout << "read error of '" << tty_map[tty_fd] << "' " 
                        ": " << strerror(errno) << endl;
                    tty_map.erase(tty_fd);
                    poller.unwatch(tty);
                    tty->close();
                }
            } 
        }

        if (tty_map.empty()) {
            cout << "all tty closed!" << endl;
            break;
        }
    }

    return 0;
}
