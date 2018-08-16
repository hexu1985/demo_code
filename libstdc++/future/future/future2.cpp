// future::future
#include <iostream>       // std::cout
#include <future>         // std::async, std::future

int get_value() { return 10; }

int main ()
{
  std::future<int> foo;                            // default-constructed
  std::future<int> bar = std::async (get_value);   // move-constructed

  int x = bar.get();

  std::cout << "value: " << x << '\n';

  return 0;
}
