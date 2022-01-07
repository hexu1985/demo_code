#include "mystring.h"
#include <iostream>

__attribute__ ((visibility("default"))) MyString::MyString()
{
  std::cout << "MyString::MyString()" << std::endl;
}

__attribute__ ((visibility("default"))) MyString::~MyString()
{
  std::cout << "MyString::~MyString()" << std::endl;
}

__attribute__ ((visibility("default"))) void MyString::print()
{
  std::cout << "MyString::print()" << std::endl;
}


