#include <boost/python.hpp>
#include "world.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World", init<std::string>())
        .def(init<double, double>())
        .def("greet", &World::greet)
        .def("set", &World::set)
        .def("sum_s", &World::sum_s)
    ;
}
