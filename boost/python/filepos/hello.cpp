#include<string>
#include<iostream>

// #include<boost/python.hpp> 如果仅包含该头文件，会出错
#include <boost/python/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/operators.hpp>

#include "filepos.h"

using namespace std;
using namespace boost::python;

BOOST_PYTHON_MODULE(hello)
{
    class_<FilePos>("FilePos")
        .def_readwrite("len",&FilePos::len)
        .def(self + int())
        .def(int() + self)
        .def(self - self)
        .def(self - int())
        .def(self += int())
        .def(self -= other<int>())
        .def(self < self)
        .def(float_(self))//特殊方法 ,     __float__
        .def(pow(self, other<FilePos>()))  // __pow__
        .def(abs(self))         //  __abs__
        .def(str(self));                //  __str__ for ostream
}
