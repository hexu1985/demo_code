#include<string>
#include<iostream>
#include<boost/python.hpp>

#include "base.h"
#include "derived.h"

using namespace std;
using namespace boost::python;

void b(Base *base) { cout << base->getName() << endl; };

void d(Derived *derived) { cout << derived->getName() << endl; };

Base *factory() { return new Derived; }

BOOST_PYTHON_MODULE(hello)
{
    class_<Base>("Base")
        .def("getName", &Base::getName)
        .def_readwrite("str", &Base::str);


    class_<Derived, bases<Base> >("Derived")
        .def("getName", &Derived::getName)
        .def_readwrite("str", &Derived::str);


    def("b", b);
    def("d", d);

    def("factory", factory, 
            return_value_policy<manage_new_object>());
}
