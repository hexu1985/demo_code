#include <boost/python.hpp>

#include <list>

using namespace boost::python;

template <typename T>
void list_assign(std::list<T> &l, object o)
{
    // Turn a Python sequence into an STL input range
    stl_input_iterator<T> begin(o), end;
    l.assign(begin, end);
}

BOOST_PYTHON_MODULE(demo)
{
    class_<std::list<int>>("list_int")
        .def("assign", &list_assign<int>)
        .def("__iter__", iterator<std::list<int>>())
        ;
}
