// new_handler example
#include <iostream>     // std::cout
#include <cstdlib>      // std::exit
#include <new>          // std::set_new_handler

void no_memory () {
  std::cout << "Failed to allocate memory!\n";
  std::exit (1);
}

int main () {
  std::set_new_handler(no_memory);
  std::cout << "Attempting to allocate 1 GiB...";
  char* p = new char [1024*1024*1024];
  std::cout << "Ok\n";
  delete[] p;
  return 0;
}

/*
Possible output:

Attempting to allocate 1 GiB... Ok
*/
