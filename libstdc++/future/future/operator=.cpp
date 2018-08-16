// future::operator=
#include <iostream>       // std::cout
#include <future>         // std::async, std::future

int get_value() { return 10; }

int main ()
{
  std::future<int> fut;           // default-constructed
  fut = std::async (get_value);   // move-assigned

  std::cout << "value: " << fut.get() << '\n';

  return 0;
}

/*
Output:

value: 10
*/
