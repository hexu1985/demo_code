#include <fcntl.h>
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

    int serial = 0;

    serial = Tty_get_modem_status(fd);
    if (TTY_MODEM_STATUS_CTS(serial)) {
        cout << "CTS is on" << endl;
    } else {
        cout << "CTS is off" << endl;
    }

    if (TTY_MODEM_STATUS_DSR(serial)) {
        cout << "DSR is on" << endl;
    } else {
        cout << "DSR is off" << endl;
    }

    if (TTY_MODEM_STATUS_DCD(serial)) {
        cout << "DCD is on" << endl;
    } else {
        cout << "DCD is off" << endl;
    }

    if (TTY_MODEM_STATUS_RI(serial)) {
        cout << "RI is on" << endl;
    } else {
        cout << "RI is off" << endl;
    }

    return 0;
}


