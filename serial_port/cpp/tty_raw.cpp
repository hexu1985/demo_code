#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include "wraptermios.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <ttyname>" << endl; 
        return 1;
    }

    int fd = Tty_open(argv[1], O_RDWR | O_NOCTTY | O_NONBLOCK);
    cout << "Open tty: " << argv[1] << " ok, " << "fd: " << fd << endl;

    Tty_raw(fd);
    cout << "Set raw ok" << endl;

    return 0;
}


