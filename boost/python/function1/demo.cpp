// 函数的调用策略 
#include<string>
#include<iostream>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

struct X {
    string str;
};

struct Z {
    int value;
};

struct Y {
    X x;
    Z *z;
    int z_value() { return z->value; }
};

X &f(Y &y, Z *z)
{
    y.z = z;
    return y.x;  //因为x是y的数据成员，x的声明周期与y进行了绑定。因为我们的目的是：Python接口应尽可能的反映C++接口
}

BOOST_PYTHON_MODULE(demo)
{
    class_<Y>("Y")
        .def_readwrite("x", &Y::x)
        .def_readwrite("z", &Y::z)
        .def("z_value", &Y::z_value);

    class_<X>("X")
        .def_readwrite("str", &X::str);

    class_<Z>("Z")
        .def_readwrite("value", &Z::value);

    // return_internal_reference<1 表示返回的值与第一个参数有关系：即第一个参数是返回对象的拥有者（y和x都是引用的形式)。
    // with_custodian_and_ward<1, 2> 表示第二个参数的生命周期依赖于第一个参数的生命周期。
    def("f", f, return_internal_reference<1, with_custodian_and_ward<1, 2> >());
}
