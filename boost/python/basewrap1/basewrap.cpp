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
        return this->get_override("f")();
    }
};

BOOST_PYTHON_MODULE(hello)
{
    class_<BaseWrap, boost::noncopyable>("Base")
        .def("f", pure_virtual(&Base::f));

    def("b", b);
}
