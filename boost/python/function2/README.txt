1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> x = demo.X()
>>> x.f(1)
bool f(int a)
True
>>> x.f(2, 3)
bool f(int a, double b)
True
>>> x.f(4, 5, 6)
bool f(int a, int b, int c)
15
>>> x.f(4, 5, '6')
bool f(int a, double b, char c)
True

3) 通过脚本调用demo.Num
$ python test_demo.py
