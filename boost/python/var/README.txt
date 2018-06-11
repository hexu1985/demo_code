1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello.Var
$ python
>>> import hello
>>> x = hello.Var('pi')
>>> x.value = 3.14
>>> print(x.name, 'is around', x.value)
pi is around 3.14

>>> x.name = 'e' # can't change name
Traceback (most recent call last):
      File "<stdin>", line 1, in ?
      AttributeError: can't set attribute

3) 通过脚本调用hello.Var
$ python test_hello.py
