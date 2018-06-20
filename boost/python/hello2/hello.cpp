//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <boost/python.hpp>
#include "dump_data.h"

void (std::vector<std::string>::*push_back)(const std::string &) = &std::vector<std::string>::push_back;

char const* greet()
{
    return "hello, world";
}

std::string greet2()
{
    std::string str = "hello, world";
    str.push_back((char) 0xf1);
    return str;
}

std::vector<uint8_t> greet3()
{
    std::string str = "hello, world";
    str.push_back((char) 0xf1);
    std::vector<uint8_t> vec;
    for (auto c: str) {
        vec.push_back((uint8_t)c);
    }
    return std::move(vec);
}

void print(const std::string &str)
{
    dump_data("str", str.data(), str.size());
}

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
    def("greet", greet);
    def("greet2", greet2);

    class_<std::vector<uint8_t>>("ByteArray")
		.def("push_back", push_back)
        .def("__iter__", iterator<std::vector<uint8_t>>());

    def("greet3", greet3);

    def("print", print);
}
