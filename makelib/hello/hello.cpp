#include <iostream>
#include <assert.h>

using namespace std;

int print_hello()
{
	cout << "hello world!" << endl;
#ifndef NDEBUG
	assert(false);
#endif
	return 1;
}
