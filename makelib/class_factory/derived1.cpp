#include "derived1.h"

#include <iostream>

using namespace std;

Derived1::Derived1()
{
	cout << "Derived1::Derived1" << endl;
}

Derived1::~Derived1()
{
	cout << "Derived1::~Derived1" << endl;
}

int Derived1::foo(const std::string &str)
{
	cout << "Derived1::foo: " << str << endl;
	return 1;
}

void Derived1::print()
{
	cout << "hello Derived1" << endl;
}

extern "C" Base *create()
{
	return new Derived1;
}

extern "C" void destroy(Base *p)
{
	delete p;
}

