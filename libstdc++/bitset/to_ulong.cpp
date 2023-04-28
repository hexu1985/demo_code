// bitset::to_ulong
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;     // foo: 0000
  foo.set();              // foo: 1111

  std::cout << foo << " as an integer is: " << foo.to_ulong() << '\n';

  return 0;
}
