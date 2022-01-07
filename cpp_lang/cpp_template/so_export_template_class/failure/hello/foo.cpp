#include "foo.h"
#include "mystring.h"
#include <iostream>

template <typename T>
Foo<T>::Foo() 
{
    std::cout << "Foo::Foo()" << std::endl;
}

template <typename T>
Foo<T>::~Foo() 
{
    std::cout << "Foo::~Foo()" << std::endl;
}

template <typename T>
void Foo<T>::print() 
{
    std::cout << "Foo::print()" << std::endl;
}

template class Foo<MyString>;

template class __attribute__ ((visibility("default"))) Foo<int>;
template class __attribute__ ((visibility("default"))) Foo<MyString>;

