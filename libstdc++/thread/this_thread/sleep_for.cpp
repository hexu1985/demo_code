// this_thread::sleep_for example
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
 
int main() 
{
  std::cout << "countdown:\n";
  for (int i=10; i>0; --i) {
    std::cout << i << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n";

  return 0;
}

/*
Output (after 10 seconds):
countdown:
10
9
8
7
6
5
4
3
2
1
Lift off!
*/
