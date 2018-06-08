1) 编译hello.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) python调用hello模块
$ python
>>> import hello
>>> planet = hello.World(5, 6)
>>> planet2 = hello.World("hollo world")
>>> planet.sum_s()
11.0
>>> planet2.greet()
'hollo world'

3) 通过脚本调用hello模块
$ python test_word.py
