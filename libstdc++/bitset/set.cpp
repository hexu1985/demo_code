// bitset::set
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;

  std::cout << foo.set() << '\n';       // 1111
  std::cout << foo.set(2,0) << '\n';    // 1011
  std::cout << foo.set(2) << '\n';      // 1111

  return 0;
}
