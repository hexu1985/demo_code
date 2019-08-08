cmake 命令行
两种使用方式：

    cmake [option] <path-to-source> 指向含有顶级CMakeLists.txt的那个目录
    cmake [option] <path-to-existing-build> 指向含有CMakeCache.txt的那个目录

第一种方式用于第一次生成cmake makefile，此后可以在build dir里直接cmake . 注意.表示当前目录，因为当前目录中已经有CMakeCache.txt，所以适用第二种方式。实际上cmake总是先检查指定的build dir中有没有CMakeCache.txt，如果有就按第二种方式处理；如果没有才寻找CMakeLists.txt使用第一种方式处理。

 
常用选项：

    -G <generator-name> 指定makefile生成器的名字。例如：cmake -G "MinGW Makefiles";注意generator是大小写敏感的，即使是在windows下。generator所用的命令(gcc,cl等)最好已经设置在环境变量PATH中。有个例外就是生成visual studio的工程不必设置环境变量，只要安装了对应的vs，cmake可以自动找到。
    -D<var>:<type>=<value> 添加变量及值到CMakeCache.txt中。注意-D后面不能有空格，type为string时可省略。例如：cmake -DCMAKE_BUILD_TYPE:STRING=Debug。MinGW Generator默认生成CMAKE_BUILD_TYPE为空，即release；NMake Generator默认生成CMAKE_BUILD_TYPE为Debug。
    -U<globbing_expr> 删除CMakeCache.txt中的变量。注意-U后面不能有空格,支持globbing表达式，比如*,?等。例如：cmake -UCMAKE_BUILD_TYPE。
--------------------- 
版权声明：本文为CSDN博主「巴依老爷」的原创文章，遵循CC 4.0 by-sa版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/darkdong/article/details/6102104
