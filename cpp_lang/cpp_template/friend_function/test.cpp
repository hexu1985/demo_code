#include <iostream>
#include <string>

template <typename T>
class A {
public:
    T val;

    A(const T& val_): val(val_) {}

    friend void print(const A& a) {
        std::cout << "A: val=" << a.val << std::endl;
    }

private:
    template <typename U>
    friend void print2(const A<U>& a); 
};

template <typename T>
void print2(const A<T>& a) {
    std::cout << "print2, A: val=" << a.val << std::endl;
}

int main() {
    A<std::string> a("hello");
    A<int> b(3);
    print(a);
    print(b);
    print2(a);
    print2(b);
}
