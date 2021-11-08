// shared_ptr::operator*
#include <iostream>
#include "shared_ptr.hpp"



int main () {
    shared_ptr<int> foo (new int);
    shared_ptr<int> bar (new int (100));

    *foo = *bar * 2;

    std::cout << "foo: " << *foo << '\n';
    std::cout << "bar: " << *bar << '\n';

    return 0;
}

/*
Output:
foo: 200
bar: 100
*/

