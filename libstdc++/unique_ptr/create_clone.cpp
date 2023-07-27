#include <memory>
#include <iostream>


class A {
public:
    A(int a_=0, int b_=0): a(a_), b(b_) {}

    std::unique_ptr<A> clone();

public:
    int a;
    int b;
};


std::unique_ptr<A> A::clone() {
    return std::unique_ptr<A>(new A{a, b});
}

int main()
{
    A a;
    auto b = a.clone();
    std::cout << a.a << b->a << std::endl;

    return 0;
}
