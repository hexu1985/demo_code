#include "foo.h"
#include "mystring.h"
#include <iostream>
#include <assert.h>

using namespace std;

extern "C" {

int __attribute__((visibility("default"))) print_hello()
{
	cout << "hello world!" << endl;
#ifndef NDEBUG
	assert(false);
#endif
	return 1;
}

}

void print_hello(int) 
{
  Foo<MyString> test;
  test.print();

	cout << "int hello world!" << endl;
}

