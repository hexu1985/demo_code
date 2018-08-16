// unique_lock::operator= example
#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock, std::try_to_lock

std::mutex mtx;           // mutex for critical section

void print_star () {
  std::unique_lock<std::mutex> lck(mtx,std::try_to_lock);
  // print '*' if successfully locked, 'x' otherwise: 
  if (lck)
    std::cout << '*';
  else                    
    std::cout << 'x';
}

int main ()
{
  std::vector<std::thread> threads;
  for (int i=0; i<500; ++i)
    threads.emplace_back(print_star);

  for (auto& x: threads) x.join();

  std::cout << '\n';

  return 0;
}

/*
Possible output (the amount of 'x' -if any- may vary):

***********************************x*****x******************x*******************
****************x**x*x*x***x***x************************x**************x********
********************************************************************************
********************************************************************************
****************************************************************x***************
***x****************************************************************************
******x**********x**
*/
