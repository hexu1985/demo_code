#include <iostream>
#include <string>
#include <stdlib.h>
#include "error.h"
#include "udp_sender.h"

using namespace std;

int
main(int argc, char **argv)
{
	if (argc != 3)
		err_quit("usage: udpcli <IPaddress> <port>");

    UdpSender udp;
    udp.connect(argv[1], atoi(argv[2]));

    string str;
    while (getline(cin, str)) //循环读取数据
    {
        udp.send(str.c_str(), str.length());
    }

	exit(0);
}
