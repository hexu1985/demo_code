#include <iostream>
#include <string>
#include <vector>

namespace lib2 {

void func1() {
    std::string str = "string";
    std::cout << "hello lib2::func1:" << str << std::endl;
    std::vector<int> vec(50);
    (void) vec;
    char *p = new char[100];
    (void) p;
}

}   // namespace lib1
