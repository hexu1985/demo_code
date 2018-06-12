1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> dlist = demo.dlist()
>>> dlist.push_back(1.0)
>>> dlist.push_back(2.0)
>>> dlist.push_back(3.0)
>>> dlist.push_back(4.0)
>>> for x in dlist:
...     print(x)
...
1.0
2.0
3.0
4.0

3) 通过脚本调用demo.Num
$ python test_demo.py
