#include <iostream>

using namespace std;


template <int I>
struct Foo {
    Foo() {
        std::cout << "Foo_" << I << " construct" << std::endl;
    }

    ~Foo() {
        std::cout << "Foo_" << I << " destroy" << std::endl;
    }
};

struct Bar {
    Foo<1> foo1;
    Foo<2> foo2;
    Foo<5> foo5;
    Foo<0> foo0;
};

int main() {
    Bar bar;
    return 0;
}
