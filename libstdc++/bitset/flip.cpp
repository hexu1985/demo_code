// bitset::flip
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo (std::string("0001"));

  std::cout << foo.flip(2) << '\n';     // 0101
  std::cout << foo.flip() << '\n';      // 1010

  return 0;
}
