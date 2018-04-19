#include <unistd.h>
#include <iostream>
#include <string>
#include "wraptermios.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <ttyname>" << endl; 
        return 1;
    }

    int fd = Tty_open_easy(argv[1]);
    cout << "Open tty: " << argv[1] << " ok, " << "fd: " << fd << endl;

    Tty_raw(fd);
    Tty_set_speed(fd, 9600);
    Tty_set_parity(fd, 8, 1, 'N');
    Tty_set_icanon(fd, 0, 0);

    int nread;
    const int BUFSIZE = 2048;
    char buff[BUFSIZE];

    string data;
    while (true) //循环读取数据
    {
        while ((nread = read(fd, buff, BUFSIZE))>0)
        {
            data.assign(buff, nread);
            cout << "read " << data.size() << " bytes: " << data << endl;
        }
        if (nread == 0) {
            break;
        }
    }

    close(fd); 
    return 0;
}
