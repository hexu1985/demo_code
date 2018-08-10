#include <iostream>
#include <fstream>
#include <stdexcept>
#include <time.h>

using namespace std;

ofstream &my_log()
{
    static ofstream *ofile = NULL;
    if (ofile == NULL) {
        ofile = new ofstream("C:\\hexu\\log.txt", ios::app);
        if (!ofile) {
            throw runtime_error("open log file error");
        }
        *ofile << "-----------------------log begin-------------------\n";
    }
    return *ofile;
}

int main()
{
    my_log() << "hello hexu" << std::endl;
    cout << "pause()" << std::endl;
    char c;
    cin >> c;

    return 0;
}
