#include <iostream>
#include <assert.h>

using namespace std;

extern "C" {

int print_hello()
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
	cout << "int hello world!" << endl;
}
