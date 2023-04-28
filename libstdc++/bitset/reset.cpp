// bitset::reset
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo (std::string("1011"));

  std::cout << foo.reset(1) << '\n';    // 1001
  std::cout << foo.reset() << '\n';     // 0000

  return 0;
}
