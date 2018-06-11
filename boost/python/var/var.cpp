#include <string>
#include <boost/python.hpp>
#include "var.h"

using namespace std;
using namespace boost::python;

BOOST_PYTHON_MODULE(hello)
{
	class_<Var>("Var", init<string>())
		.def_readonly("name", &Var::name)
		.def_readwrite("value", &Var::value);
}
