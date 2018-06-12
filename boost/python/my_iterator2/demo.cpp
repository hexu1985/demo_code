#include <boost/python.hpp>

#include <string>
#include "list.h"

//using namespace boost::python;

BOOST_PYTHON_MODULE(demo)
{
    boost::python::class_<list<double>>("dlist")
		.def("push_back", &list<double>::push_back)
        .def("__iter__", boost::python::iterator<list<double>>())
        ;
}
