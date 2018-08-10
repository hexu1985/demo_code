#include <ctime>       /* time_t, struct tm, time, localtime, strftime */
#include <string>
#include <iostream>

std::string time_now_str()
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80] = {};
  time(&rawtime);
  timeinfo = localtime (&rawtime);
  strftime (buffer, 80, "%A %c",timeinfo);
  return std::string(buffer);
}

int main ()
{
  std::string str = time_now_str();
  std::cout << "Now: " << str << std::endl;

  return 0;
}


/*
Example output:

Now it's 03:21PM.
*/

