#include <iostream>

using namespace std;

struct Foo {
    int val_ = 0;
    Foo()
    {
        cout << "Foo()" << endl;
    }

    Foo(int val): val_(val)
    {
        cout << "Foo(int)" << endl;
    }

    Foo(const Foo &x): val_(x.val_)
    {
        cout << "Foo(const Foo &x)" << endl;
    }

    Foo(Foo &&x): val_(x.val_)
    {
        x.val_ = -1;
        cout << "Foo(Foo &&x)" << endl;
    }

    Foo &operator =(const Foo &x)
    {
        val_ = x.val_;
        cout << "Foo &operator =(const Foo &x)" << endl;
        return *this;
    }

    Foo &operator =(Foo &&x)
    {
        val_ = x.val_;
        x.val_ = -1;
        cout << "Foo &operator =(Foo &&x)" << endl;
        return *this;
    }
};

int main()
{
    cout << "test move reference" << endl;
    {
        Foo a;
        Foo b(20);
        Foo &c = b;
        cout << "a.val_: " << a.val_ << endl;
        cout << "b.val_: " << b.val_ << endl;
        a = std::move(c);
        cout << "a.val_: " << a.val_ << endl;
        cout << "b.val_: " << b.val_ << endl;
    }
    return 0;
}
