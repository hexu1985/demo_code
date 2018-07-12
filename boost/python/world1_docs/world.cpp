#include <boost/python.hpp>
#include "world.h"

using namespace boost::python;

const char *set_docs =
R"(set docs of set
demo
yyy
)";

BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World")
        .def("greet", &World::greet, "greet docs of World\n demo: \n xxx")
        .def("set", &World::set, set_docs)
    ;
}
