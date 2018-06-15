#include <string>
#include <iostream>
#include <boost/python.hpp>
#include <numpy/arrayobject.h>

using namespace std;
using namespace boost::python;

namespace bp = boost::python;

void f(object x)
{
    int y = extract<int>(x); // retrieve an int from x
}

int g(object x)
{
    extract<int> get_int(x);
    if (get_int.check())
        return get_int();
    else
        return 0;
}

int test(object &x)
{
    dict d = extract<dict>(x.attr("__dict__"));
    d["whatever"] = 4;
    return 0;
}

int test2(dict &d)
{
    d["helloworld"] = 3;
    return 0;
}

class A {
public:
    list lst;
    void listOperation(list &lst) {};
};

// 传入np.array数组对象，让C++进行处理
int add_arr_1(object &data_obj, object rows_obj, object cols_obj)
{
    PyArrayObject* data_arr = reinterpret_cast<PyArrayObject*>(data_obj.ptr());
    float * data = static_cast<float *>(PyArray_DATA(data_arr));
    // using data
    int rows = extract<int>(rows_obj);
    int cols = extract<int>(cols_obj);
    for (int i = 0; i < rows*cols; i++)
    {
        data[i] += 1;
    }
    return 0;
}

BOOST_PYTHON_MODULE(demo)
{
    def("test", test);
    def("test2", test2);
    def("add_arr_1", add_arr_1);
}
