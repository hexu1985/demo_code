// init  optional

#include<string>
#include<iostream>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct X {
    X(int a, char b = 'D', string c = "constructor", double d = 0.0) 
    {
        cout << "a = " << a << ", "
            << "b = " << b << ", "
            << "c = " << c << ", "
            << "d = " << d << endl;
    }
};

BOOST_PYTHON_MODULE(demo)
{
    class_<X>("X",
        init<int, optional<char, string, double> >()); // init 和 optional
}
