// notify_all_at_thread_exit
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id (int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!ready) cv.wait(lck);
  // ...
  std::cout << "thread " << id << '\n';
}

void go() {
  std::unique_lock<std::mutex> lck(mtx);
  std::notify_all_at_thread_exit(cv,std::move(lck));
  ready = true;
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_id,i);
  std::cout << "10 threads ready to race...\n";

  std::thread(go).detach();   // go!

  for (auto& th : threads) th.join();

  return 0;
}

/*
Possible output (order of threads may vary):

10 threads ready to race...
thread 9
thread 0
thread 7
thread 2
thread 5
thread 4
thread 6
thread 8
thread 3
thread 1
*/
