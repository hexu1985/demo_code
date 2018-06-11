1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello.Num
$ python
>>> from hello import Num
>>> x = Num()
>>> x.value = 3.14
>>> x.value, x.rovalue
(3.14, 31.4)

>>> x.rovalue = 2.17  # error!
Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      AttributeError: can't set attribute

3) 通过脚本调用hello.Num
$ python test_hello.py
