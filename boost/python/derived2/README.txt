1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello.factory
$ python
>>> import hello
>>> x = hello.factory()
>>> hello.d(x)
Derived
>>> hello.b(x)
Derived

3) 通过脚本调用hello.factory
$ python test_hello.py
