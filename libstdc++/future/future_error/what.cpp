// future_error::what example:
#include <iostream>     // std::cout
#include <future>       // std::promise, std::future_error

int main ()
{
  std::promise<int> prom;

  try {
    prom.get_future();
    prom.get_future();   // throws std::future_error
  }
  catch (std::future_error& e) {
    std::cout << "future_error caught: " << e.what() << '\n';
  }

  return 0;
}


/*
Possible output (the message is implementation-specific):

future_error caught: promise already satisfied
*/
