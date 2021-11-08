// shared_ptr i/o
#include <iostream>
#include "shared_ptr.hpp"



int main () {
	shared_ptr<int> foo (new int (10));

	std::cout << " foo: " << foo << '\n';
	std::cout << "*foo: " << *foo << '\n';

	return 0;
}

/*
Possible output:
foo: 0x920d90
*foo: 10
*/

