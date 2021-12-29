// time_point::time_since_epoch
#include <iostream>
#include <chrono>

int main ()
{
  using namespace std::chrono;

  system_clock::time_point tp = system_clock::now();
  system_clock::duration dtn = tp.time_since_epoch();

  std::cout << "current time since epoch, expressed in:" << std::endl;
  std::cout << "periods: " << dtn.count() << std::endl;
  std::cout << "milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(dtn).count() << std::endl;
  std::cout << "seconds: " << std::chrono::duration_cast<std::chrono::seconds>(dtn).count() << std::endl;
  std::cout << std::endl;

  return 0;
}

/*
Possible output:
current time since epoch, expressed in:
periods: 1640770237365008894
milliseconds: 1640770237365
seconds: 1640770237
*/
