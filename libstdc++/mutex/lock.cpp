// std::lock example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock

std::mutex foo,bar;

void task_a () {
  // foo.lock(); bar.lock(); // replaced by:
  std::lock (foo,bar);
  std::cout << "task a\n";
  foo.unlock();
  bar.unlock();
}

void task_b () {
  // bar.lock(); foo.lock(); // replaced by:
  std::lock (bar,foo);
  std::cout << "task b\n";
  bar.unlock();
  foo.unlock();
}

int main ()
{
  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();

  return 0;
}

/*
Note that before replacing the individual locks by the call to std::lock, if task_a locked foo while task_b locked bar, neither could ever get the second lock, causing a deadlock.

Possible output (order of lines may vary):

task a
task b
*/
