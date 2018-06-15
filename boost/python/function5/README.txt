1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> g = demo.george()
>>> g.wack_em(1)
a = 1, b = 0, c = x
>>> g.wack_em(1, 2)
a = 1, b = 2, c = x

>>> g.wack_em(1, 2, 3)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
Boost.Python.ArgumentError: Python argument types in
    george.wack_em(george, int, int, int)
did not match C++ signature:
    wack_em(george {lvalue}, int)
    wack_em(george {lvalue}, int, int)
    wack_em(george {lvalue}, int, int, char)

>>> g.wack_em(1, 2, chr(67))
a = 1, b = 2, c = C
>>> g.wack_em(1, 2, 'c')
a = 1, b = 2, c = c

3) 通过脚本调用demo.Num
$ python test_demo.py
