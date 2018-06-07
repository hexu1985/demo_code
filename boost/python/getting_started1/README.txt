1) 编译getting_started1模块
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) python调用getting_started1模块
$ python
>>> import getting_started1
>>> getting_started1.greet()
'hello, world'
>>> getting_started1.square(5)
25

3) 通过脚本调用getting_started1模块
$ python test_getting_started1.py
