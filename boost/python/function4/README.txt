1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> from demo import *
>>> foo(1)
a = 1, b = b, c = 2, d = 3
>>> foo(1, 2)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
Boost.Python.ArgumentError: Python argument types in
    demo.foo(int, int)
did not match C++ signature:
    foo(int)
    foo(int, char)
    foo(int, char, unsigned int)
    foo(int, char, unsigned int, double)
>>> foo(1, '2')
a = 1, b = 2, c = 2, d = 3
>>> foo(1, '2', 3)
a = 1, b = 2, c = 3, d = 3
>>> foo(1, chr(65), 3, 4)
a = 1, b = A, c = 3, d = 4
>>> foo(1, '2', 3, 4)
a = 1, b = 2, c = 3, d = 4

3) 通过脚本调用demo.Num
$ python test_demo.py
