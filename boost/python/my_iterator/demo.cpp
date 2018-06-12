#include <boost/python.hpp>

#include <string>
#include "d_list.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(demo)
{
    class_<miniList<double>>("dlist")
		.def("push_back", &miniList<double>::push_back)
        .def("__iter__", boost::python::iterator<miniList<double>>())
        ;
}
