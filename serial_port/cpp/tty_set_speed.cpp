#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include "wraptermios.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <ttyname> <speed>" << endl; 
        return 1;
    }

    int fd = Tty_open(argv[1], O_RDWR | O_NOCTTY | O_NONBLOCK);
    cout << "Open tty: " << argv[1] << " ok, " << "fd: " << fd << endl;

    Tty_set_speed(fd, atoi(argv[2]));
    cout << "Set tty speed: " << argv[2] << " bit/s ok" << endl;

    return 0;
}


