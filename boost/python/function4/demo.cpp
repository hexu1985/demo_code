// BOOST_PYTHON_FUNCTION_OVERLOADS

#include<string>
#include<iostream>

#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

void foo(int a, char b = 'b', unsigned c = 2, double d = 3)
{
    cout << "a = " << a << ", "
        << "b = " << b << ", "
        << "c = " << c << ", "
        << "d = " << d << endl;

    return;
}

BOOST_PYTHON_FUNCTION_OVERLOADS(foo_overloads, foo, 1, 4); // 参数个数的最小为1，最大为4

BOOST_PYTHON_MODULE(demo)
{
    def("foo", foo, foo_overloads()); //实现导出带有默认参数的函数
}
