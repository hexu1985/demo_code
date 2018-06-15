#include<string>
#include<iostream>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

int f(int x, double y = 3.14, char const *z = "hello")
{
    cout << "x = " << x << ", "
        << "y = " << y << ", "
        << "z = " << z << "."
        << endl;
    return 1;
}

int f1(int x)
{
    return f(x);
}

int f2(int x,double y)
{
    return f(x,y);
}

BOOST_PYTHON_MODULE(demo)
{
    //int module init
    def("f",f); // 所有参数
    def("f",f2); //两个参数
    def("f",f1); //一个参数
}
