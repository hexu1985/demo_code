// bitset::size
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<8> foo;
  std::bitset<4> bar;

  std::cout << "foo.size() is " << foo.size() << '\n';
  std::cout << "bar.size() is " << bar.size() << '\n';

  return 0;
}
