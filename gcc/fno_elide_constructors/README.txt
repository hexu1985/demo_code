在使用GNU/g++编译器时可以使用"-fno-elide-constructors"选项来强制g++总是调用copy构造函数，即使在用临时对象初始化另一个同类型对象的时候。
