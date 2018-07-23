1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> demo.greet()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
RuntimeError: hello

3) 通过脚本调用demo.Num
$ python test_demo.py
