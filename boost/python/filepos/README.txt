1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello.Num
$ python
>>> from hello import Num
>>> filepos1 = hello.FilePos()
>>> filepos1.len = 10
>>> filepos2 = hello.FilePos()
>>> filepos2.len = 20
>>> print(filepos1 - filepos2)
-10

3) 通过脚本调用hello.Num
$ python test_hello.py
