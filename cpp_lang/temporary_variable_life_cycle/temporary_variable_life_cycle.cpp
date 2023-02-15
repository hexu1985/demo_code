#include <string.h>
#include <iostream>

struct Foo {
    char* p = nullptr;

    Foo(const std::string& s) {
        std::cout << "Foo(" << s << ")" << std::endl;
        p = new char[s.size()+1];
        strcpy(p, s.c_str());
    }

    ~Foo() {
        std::cout << "~Foo()" << std::endl;
        delete [] p;
    }

    const char* c_str() const {
        return p;
    }

    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;

    Foo(Foo&& rhs) {
        p = rhs.p;
        rhs.p = nullptr;
    }

    Foo& operator=(Foo&& rhs) {
        if (this == &rhs) return *this;

        delete [] p;
        p = rhs.p;
        rhs.p = nullptr;
        return *this;
    }
};

Foo MakeFoo(const std::string& s) {
    return Foo(s);
}

void print(const char* str) {
    std::cout << "print(" << str << ")" << std::endl;
}

int main() {
    print(MakeFoo("hello world!").c_str());
    return 0;
}
