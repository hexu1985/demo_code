1) 编译demo.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用demo.Num
$ python
>>> import demo
>>> import numpy as np
>>> dic1 = {'whatever':1}
>>> demo.test2(dic1)
0
>>> dic1
{'whatever': 1, 'helloworld': 3}
>>> arr = np.array([1,2,3], dtype = np.float32)
>>> print(arr.dtype)
float32
>>> print(arr)
[1. 2. 3.]
>>> demo.add_arr_1(arr, 1, 3)
0
>>> print(arr)
[2. 3. 4.]

3) 通过脚本调用demo.Num
$ python test_demo.py

4) 需要安装numpy
$ sudo pacman -S python-numpy
