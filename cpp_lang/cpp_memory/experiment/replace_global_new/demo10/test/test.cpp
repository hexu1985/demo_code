#include "lib1.hpp"
#include "lib2.hpp"
#include <iostream>
#include <string>
#include <vector>

void func1() {
    std::string str = "func1";
    std::cout << "hello " << str << std::endl;
    std::vector<int> vec(50);
    (void) vec;
}

int main()
{
    lib1::func1();
    lib2::func1();
    func1();
    return 0;
}

