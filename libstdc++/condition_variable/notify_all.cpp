// condition_variable_any::notify_all
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable_any

std::mutex mtx;
std::condition_variable_any cv;
bool ready = false;

void print_id (int id) {
  mtx.lock();
  while (!ready) cv.wait(mtx);
  // ...
  std::cout << "thread " << id << '\n';
  mtx.unlock();
}

void go() {
  mtx.lock();
  ready = true;
  cv.notify_all();
  mtx.unlock();
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_id,i);

  std::cout << "10 threads ready to race...\n";
  go();                       // go!

  for (auto& th : threads) th.join();

  return 0;
}

/*
Possible output (thread order may vary):

10 threads ready to race...
thread 6
thread 2
thread 5
thread 3
thread 4
thread 1
thread 7
thread 0
thread 9
thread 8
*/
