#include<string>
#include<boost/python.hpp>
#include "num.h"

using namespace std;
using namespace boost::python;

BOOST_PYTHON_MODULE(hello)
{
    class_<Num>("Num")
        .add_property("rovalue", &Num::get) // 对外：只读
        .add_property("value", &Num::get, &Num::set);// 对外读写 .value值会改变.rovalue值，存储着同样的数据。
}
