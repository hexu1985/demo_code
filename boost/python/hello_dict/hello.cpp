//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <string>
#include <map>
#include <boost/python.hpp>

boost::python::dict greet()
{
    std::map<std::string, std::string> m = {
        {"key1", "val1"},
        {"key2", "val2"},
        {"key3", "val3"}
    };

    boost::python::dict d;

    for (auto &pair: m) {
        d[pair.first] = pair.second;
    }

    return d;
}

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
    def("greet", greet);
}
