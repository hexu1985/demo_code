#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "boost/thread.hpp"
#include "auto_timestamp_ofile.h"

using namespace std;

void auto_timestamp_ofile_test()
{
    string prefix = "FILE";
    string suffix = ".txt";

    AutoTimestampOFile ofile(prefix, suffix);

    string str;
    while (getline(cin, str)) //循环读取数据
    {
        ofile.write(str.c_str(), str.length());
        boost::this_thread::interruption_point();
    }

    cout << "file size: " << ofile.size() << endl;
}

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
    boost::thread thr(&auto_timestamp_ofile_test);

    while (!sigint_flag) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    cout << "to interrupt thread" << endl;
    thr.interrupt();
    thr.join();
    return 0;
}
