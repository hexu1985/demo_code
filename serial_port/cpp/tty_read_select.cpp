#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "wrapunix.h"
#include "wraptermios.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <ttyname1> [ttypname2] [ttyname3] ..." << endl; 
        return 1;
    }

    std::map<int, std::string> tty_map;
    std::vector<int> tty_fds;

    for (int i = 1; i < argc; i++) {
        int fd = Tty_open_easy(argv[i]);
        cout << "Open tty: " << argv[i] << " ok, " << "fd: " << fd << endl;

        Tty_set_speed(fd, 9600);
        Tty_set_parity(fd, 8, 1, 'N');
        Tty_set_icanon(fd, 0, 0);

        tty_fds.push_back(fd);
        tty_map.insert(std::make_pair(fd, std::string(argv[i])));
    }

    fd_set rset, allset;  
    FD_ZERO(&allset);
    int maxfd = *std::max_element(tty_fds.begin(), tty_fds.end());
    for (int i = 0; i < tty_fds.size(); i++) {
        FD_SET(tty_fds[i], &allset);
    }

    int nread;
    const int BUFSIZE = 2048;
    char buff[BUFSIZE];

    string data;
    for ( ; ; ) {
        rset = allset;
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100 * 1000;

        int nready = Select(maxfd+1, &rset, NULL, NULL, &timeout);
        if (nready == 0) {  // timeout
            cerr << ".";
        }

        for (int i = 0; i < tty_fds.size(); i++) {
            if (FD_ISSET(tty_fds[i], &rset)) {
                nread = read(tty_fds[i], buff, BUFSIZE);
                if (nread > 0) {
                    data.assign(buff, nread);
                    cout << "\nread from '" << tty_map[tty_fds[i]] << "' " << data.size() << " bytes: " << data << endl;
                }
            }
        }
    }

    for (int i = 0; i < tty_fds.size(); i++) {
        close(tty_fds[i]); 
    }

    return 0;
}
