1) 编译hello_ext.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello_ext
$ python
>>> import hello_ext
>>> hello_ext.greet()
'hello, world'

3) 通过脚本调用hello_ext
$ python test_hello.py
