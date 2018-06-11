1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello
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
Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      RuntimeError: Pure virtual function called

3) 通过脚本调用hello
$ python test_hello.py
