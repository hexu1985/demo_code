//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <string>
#include <stdexcept>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

class MyException: public std::runtime_error {
public: 
    MyException(const std::string &msg): std::runtime_error(msg) {}
}; 

char const* greet()
{
   throw MyException("hello");
   return "hello, world";
}

BOOST_PYTHON_MODULE(demo)
{
    using namespace boost::python;
    def("greet", greet);
}

