#include <boost/python.hpp>

#include <vector>

using namespace boost::python;

void (std::vector<double>::*push_back)(const double &) = &std::vector<double>::push_back;

double &at(std::vector<double> &vec, size_t i)
{
    return vec.at(i);
}

BOOST_PYTHON_MODULE(demo)
{
    class_<std::vector<double>>("dvec")
		.def("push_back", push_back)
        .def("__iter__", iterator<std::vector<double>>())
        ;

    def("at", at, return_value_policy<copy_non_const_reference>());
}
