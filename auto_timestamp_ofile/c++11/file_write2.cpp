#include <iostream>
#include <string>
#include "auto_timestamp_ofile.h"

using namespace std;

int main(int argc, char *argv[])
{
    string prefix = "FILE";
    string suffix = ".txt";

    AutoTimestampOFile ofile(prefix, suffix);

    string str;
    while (getline(cin, str)) //循环读取数据
    {
        ofile.write(str.c_str(), str.length());
        ofile.flush();
    }

    cout << "file size: " << ofile.size() << endl;

    return 0;
}
