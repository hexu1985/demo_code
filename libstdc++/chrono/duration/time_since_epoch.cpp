// time_point::time_since_epoch
#include <iostream>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  system_clock::time_point tp = system_clock::now();
  system_clock::duration dtn = tp.time_since_epoch();

  std::cout << "current time since epoch, expressed in:" << std::endl;
  std::cout << "seconds: " << duration<double>(dtn).count();
  std::cout << std::endl;

  return 0;
}
