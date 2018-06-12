#include <boost/python.hpp>

#include <vector>

using namespace boost::python;

BOOST_PYTHON_MODULE(demo)
{
    class_<std::vector<double> >("dvec")
		.def("push_back", &std::vector<double>::push_back)
        .def("__iter__", iterator<std::vector<double> >())
        ;
}
