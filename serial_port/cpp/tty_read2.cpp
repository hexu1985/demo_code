#include <unistd.h>
#include <iostream>
#include <string>
#include "wraptermios.h"
#include "tty_reader.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <ttyname>" << endl; 
        return 1;
    }

    TtyReader tty;
    tty.open(argv[1]);
    cout << "Open tty: " << argv[1] << " ok, " << "fd: " << tty.fileno() << endl;

    tty.setSpeed(9600);
    tty.setParity(8, 1, 'N');
    tty.setIcanon(0, 0);

    int nread;
    const int BUFSIZE = 2048;
    char buff[BUFSIZE];

    string data;
    while (true) //循环读取数据
    {
        while ((nread = tty.read(buff, BUFSIZE))>0)
        {
            data.assign(buff, nread);
            cout << "read " << data.size() << " bytes: " << data << endl;
        }
        if (nread == 0) {
            break;
        }
    }

    tty.close(); 
    return 0;
}
