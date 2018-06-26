// stoul example
#include <iostream>   // std::cin, std::cout
#include <string>     // std::string, std::stoul, std::getline

int main ()
{
  std::string str;
  std::cout << "Enter an unsigned number: ";
  std::getline (std::cin,str);
  unsigned long ul = std::stoul (str,nullptr,0);
  std::cout << "You entered: " << ul << '\n';
  return 0;
}
