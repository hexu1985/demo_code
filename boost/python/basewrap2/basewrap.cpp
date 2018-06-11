#include<boost/python.hpp>
#include<boost/python/wrapper.hpp>
#include<string>
#include<iostream>

#include "base.h"

using namespace boost::python;
using namespace std;

struct BaseWrap: Base, wrapper<Base>
{
    int f()
    {
        if (override f = this->get_override("f"))
            return f(); //如果函数进行重载了，则返回重载的
        return Base::f(); //否则返回基类
    }
    int default_f() { return this->Base::f(); }
};

BOOST_PYTHON_MODULE(hello)
{
    class_<BaseWrap, boost::noncopyable>("Base")
        .def("f", &Base::f, &BaseWrap::default_f);

    def("b", b);
}
