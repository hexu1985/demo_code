// bitset::operator[]
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;

  foo[1]=1;             // 0010
  foo[2]=foo[1];        // 0110

  std::cout << "foo: " << foo << '\n';

  return 0;
}
