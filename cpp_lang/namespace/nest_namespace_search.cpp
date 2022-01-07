#include <iostream>

int a = 4;

namespace A {

int a = 3;

namespace B {

void print_a()
{
    std::cout << "a: " << a << std::endl;
}

}

}

int main()
{
    A::B::print_a();
    return 0;
}
