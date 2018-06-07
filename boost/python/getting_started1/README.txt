1) 编译getting_started1.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用getting_started1
$ python
> import getting_started1
> getting_started1.greet()
> getting_started1.square(5)

3) 通过脚本调用getting_started1
$ python test_getting_started1
