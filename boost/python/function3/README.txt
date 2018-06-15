1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> from demo import *
>>> f(1)
x = 1, y = 3.14, z = hello.
1
>>> f(1, 2)
x = 1, y = 2, z = hello.
1
>>> f(2, 3, 'xxx')
x = 2, y = 3, z = xxx.
1

3) 通过脚本调用demo.Num
$ python test_demo.py
