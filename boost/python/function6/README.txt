1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> x = demo.X(1)
a = 1, b = D, c = constructor, d = 0
>>> x = demo.X(1, 2)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
Boost.Python.ArgumentError: Python argument types in
    X.__init__(X, int, int)
did not match C++ signature:
    __init__(_object*, int)
    __init__(_object*, int, char)
    __init__(_object*, int, char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
    __init__(_object*, int, char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, double)
>>> x = demo.X(1, '2')
a = 1, b = 2, c = constructor, d = 0
>>> x = demo.X(1, '2', 'adfs')
a = 1, b = 2, c = adfs, d = 0
>>> x = demo.X(1, '2', 'adfs', 4)
a = 1, b = 2, c = adfs, d = 4

3) 通过脚本调用demo.Num
$ python test_demo.py
