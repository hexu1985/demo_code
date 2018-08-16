// put_time example
#include <iostream>     // std::cout
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock

int main ()
{
  using std::chrono::system_clock;
  std::time_t tt = system_clock::to_time_t (system_clock::now());

  struct std::tm * ptm = std::localtime(&tt);
  std::cout << "Now (local time): " << std::put_time(ptm,"%c") << '\n';

  return 0;
}

/*
Possible output:
Now (local time): 03/07/13 11:41:3
*/
