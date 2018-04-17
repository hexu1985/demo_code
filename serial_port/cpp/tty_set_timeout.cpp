#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include "wraptermios.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 5) {
        cout << "usage: " << argv[0] << " <ttyname> <min> <sec> <millisec>" << endl; 
        return 1;
    }

    int fd = Tty_open(argv[1], O_RDWR | O_NOCTTY | O_NONBLOCK);
    cout << "Open tty: " << argv[1] << " ok, " << "fd: " << fd << endl;

    Tty_set_timeout(fd, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    cout << "Set parity ok, " 
        << "min: " << argv[2] << ", "
        << "sec: " << argv[3] << ", "
        << "millisec: " << argv[4] << ". " << endl;

    return 0;
}


