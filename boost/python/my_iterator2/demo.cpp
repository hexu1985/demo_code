#include <boost/python.hpp>

#include <string>
#include "list.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(demo)
{
    class_<Hx::list<double>>("dlist")
		.def("push_back", &Hx::list<double>::push_back)
        .def("__iter__", iterator<Hx::list<double>>())
        ;
}
