#include <iostream>
#include <fstream>
#include <stdexcept>
#include <time.h>

using namespace std;

string time_now_str()
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80] = {};
  time(&rawtime);
  timeinfo = localtime (&rawtime);
  strftime (buffer, 80, "%A %c",timeinfo);
  return string(buffer);
}

ofstream &my_log()
{
    static ofstream *ofile = NULL;
    if (ofile == NULL) {
        ofile = new ofstream("C:\\hexu\\log.txt", ios::app);
        if (!ofile) {
            throw runtime_error("open log file error");
        }
        *ofile << "-----------------------log begin-------------------\n";
        *ofile << time_now_str() << std::endl;
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
