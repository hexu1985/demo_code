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

    Tty_set_speed(fd, 9600);
    Tty_set_parity(fd, 8, 1, 'N');

    string str;
    while (getline(cin, str)) //循环读取数据
    {
        write(fd, str.c_str(), str.length());
    }

    close(fd); 
    return 0;
}
