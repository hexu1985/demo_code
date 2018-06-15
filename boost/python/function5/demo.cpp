//使用BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS 宏，完成成员函数默认参数的接口

#include<string>
#include<iostream>

#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct george {
    void wack_em(int a, int b = 0, char c = 'x')
    {
        cout << "a = " << a << ", "
            << "b = " << b << ", "
            << "c = " << c << endl;

        return;
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(george_overloads, wack_em, 1, 3); // 参数个数的最小为1，最大为3

BOOST_PYTHON_MODULE(demo)
{
    class_<george>("george")
        .def("wack_em", &george::wack_em, george_overloads());
}
