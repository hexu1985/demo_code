// unique_lock::mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock, std::defer_lock

class MyMutex : public std::mutex {
  int _id;
public:
  MyMutex (int id) : _id(id) {}
  int id() {return _id;}
};

MyMutex mtx (101);

void print_ids (int id) {
  std::unique_lock<MyMutex> lck (mtx);
  std::cout << "thread #" << id << " locked mutex " << lck.mutex()->id() << '\n';
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_ids,i+1);

  for (auto& th : threads) th.join();

  return 0;
}

/*
Possible output (order of lines may vary, but they are never intermingled):

thread #2 locked mutex 101
thread #3 locked mutex 101
thread #1 locked mutex 101
thread #4 locked mutex 101
thread #5 locked mutex 101
thread #6 locked mutex 101
thread #7 locked mutex 101
thread #8 locked mutex 101
thread #9 locked mutex 101
thread #10 locked mutex 101
*/
