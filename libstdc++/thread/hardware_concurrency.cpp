#include <iostream>
#include <thread>
 
int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}

/*
Possible output:

4 concurrent threads are supported.
*/
