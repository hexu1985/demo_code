1) 编译hello_ext.so
$ make
# 如果想要生成python2的module, 需要修改Makefile中的INCLUDES和LDFLAGS  

2) 调用hello_ext
$ python
>>> import hello_ext
>>> hello_ext.greet()
'hello, world'

>>> hello_ext.greet2()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 12: unexpected end of data

>>> v = hello_ext.greet3()
>>> v
<hello_ext.ByteArray object at 0x7f8469c09930>
>>> bytes(v)
b'hello, world\xf1'

>>> hello_ext.print(v)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
Boost.Python.ArgumentError: Python argument types in
    hello_ext.print(ByteArray)
did not match C++ signature:
    print(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)

>>> hello_ext.print(bytes(v))
str, data len: 13
ascii:  h  e  l  l  o  ,     w  o  r  l  d  . 
hex:   68 65 6c 6c 6f 2c 20 77 6f 72 6c 64 f1 




3) 通过脚本调用hello_ext
$ python test_hello.py
