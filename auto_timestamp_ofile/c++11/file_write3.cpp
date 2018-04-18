#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "auto_timestamp_ofile.h"

using namespace std;

volatile int sigint_flag = 0;

void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    sigint_flag = 1;
}

void register_sigint()
{
    struct sigaction act;

    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, 0);
}

int main(int argc, char *argv[])
{
    register_sigint();

    string prefix = "FILE";
    string suffix = ".txt";

    AutoTimestampOFile ofile(prefix, suffix);

    string str;
    while (!sigint_flag && getline(cin, str)) //循环读取数据
    {
        ofile.write(str.c_str(), str.length());
    }

    cout << "file size: " << ofile.size() << endl;

    return 0;
}
