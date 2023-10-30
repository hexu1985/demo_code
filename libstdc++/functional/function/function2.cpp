#include <iostream>
#include <functional>

class A {
private:
    int val;
public:
    A(int v=0): val(v) {
        std::cout << "construct A(" << val << ")" << std::endl;
    }

    ~A() {
        std::cout << "destroy A(" << val << ")" << std::endl;
    }
};

A* create_A(int v) {
    return new A{v};
}

int main()
{
    std::function<A* (int)> c;
    c = create_A;

    c(1);
    c(2);

    return 0;
}
