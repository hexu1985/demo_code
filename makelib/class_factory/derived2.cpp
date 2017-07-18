#include "derived2.h"

#include <iostream>

using namespace std;

Derived2::Derived2()
{
	cout << "Derived2::Derived2" << endl;
}

Derived2::~Derived2()
{
	cout << "Derived2::~Derived2" << endl;
}

int Derived2::foo(const std::string &str)
{
	cout << "Derived2::foo: " << str << endl;
	return 2;
}

void Derived2::print()
{
	cout << "hello Derived2" << endl;
}

extern "C" Base *create()
{
	return new Derived2;
}

