1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

$ python
>>> from hello import *
>>> base = Base()
>>> class Derived(Base):
...     def f(self):
...         return 42
...
>>> derived = Derived()
>>> derived.f()
42
>>> base.f()
0

2) 通过脚本调用hello
$ python test_hello.py
