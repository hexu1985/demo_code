1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> from demo import *
>>> x = X()
>>> y = Y()
>>> z = Z()
>>> x.str = 'hello'
>>> y.x = x
>>> y.x.str
'hello'
>>> x.str = 'world'
>>> y.x.str
'hello'
>>> z.value = 3
>>> y.z = z
>>> y.z.value
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: No to_python (by-value) converter found for C++ type: Z*
>>> y.z_value()
3
>>> z.value = 6
>>> y.z_value()
6
>>> x2 = f(y, z)
>>> x2.str
'hello'

3) 通过脚本调用demo.Num
$ python test_demo.py
