// overloading

#include<string>
#include<iostream>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct X {
    bool f(int a)
    {
        cout << "bool f(int a)" << endl;
        return true;
    }

    bool f(int a, double b)
    {
        cout << "bool f(int a, double b)" << endl;
        return true;
    }

    bool f(int a, double b, char c)
    {
        cout << "bool f(int a, double b, char c)" << endl;
        return true;
    }

    int f(int a, int b, int c)
    {
        cout << "bool f(int a, int b, int c)" << endl;
        return a + b + c;
    }
};

bool (X::*fx1)(int) = &X::f;
bool(X::*fx2)(int, double) = &X::f;
bool(X::*fx3)(int, double,char) = &X::f;
int(X::*fx4)(int, int,int) = &X::f;

BOOST_PYTHON_MODULE(demo)
{
    class_<X>("X")
        .def("f", fx1)
        .def("f", fx2)
        .def("f", fx3)
        .def("f", fx4);
}
