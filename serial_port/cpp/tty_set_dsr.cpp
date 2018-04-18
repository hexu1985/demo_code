#include <fcntl.h>
#include <iostream>
#include "wraptermios.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <ttyname> <on|off>" << endl; 
        return 1;
    }

    int fd = Tty_open(argv[1], O_RDWR | O_NOCTTY | O_NONBLOCK);
    cout << "Open tty: " << argv[1] << " ok, " << "fd: " << fd << endl;

    int serial = 0;

    serial = Tty_get_modem_status(fd);
    if (is_modem_status_dsr(serial)) {
        cout << "DSR is on" << endl;
    } else {
        cout << "DSR is off" << endl;
    }

    if (argv[2] == std::string("on")) {
        cout << "Now set DSR flag" << endl;
        set_modem_status_dsr(serial);
    } else {
        cout << "Now unset DSR flag" << endl;
        unset_modem_status_dsr(serial);
    }

    Tty_set_modem_status(fd, serial);

    serial = Tty_get_modem_status(fd);
    if (is_modem_status_dsr(serial)) {
        cout << "DSR is on" << endl;
    } else {
        cout << "DSR is off" << endl;
    }

    return 0;
}


