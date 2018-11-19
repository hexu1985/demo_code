一、obfuscator-llvm编译
1) 下载项目并编译
$ git clone -b llvm-4.0 https://github.com/obfuscator-llvm/obfuscator.git
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ../obfuscator/
$ make -j7

二、以插件的方式提供
https://github.com/obfuscator-llvm/obfuscator/wiki/Installation

三、验证
1) 打开Xcode: 
    -> Create a new Xcode project
    -> Choose a template for your new project: 选macOS/Application: Command Line Tool
    -> Choose options for your new project:
        -> Product Name: 自己输入
        -> Organization Identifier: 自己输入
        -> Language: 选C++
2) 编辑代码

3) 修改编译器
点击项目图标:
    -> Build Settings: 选择All和Combined,
        -> Build Options
            -> Compiler for C/C++/Objective-C: 选择Obfuscator4.0

4) 修改编译器选项
点击项目图标:
    -> Build Settings: 选择All和Combined,
        -> Obfuscator 4.0 - Custom Compiler Flags
            -> Other C++ Flags: 增加 -mllvm -fla

5) 修改C++标准库
点击项目图标:
    -> Build Settings: 选择All和Combined,
        -> Obfuscator 4.0 - Language - C++
            -> C++ Standard Library: 选libstdc++(GNU C++ standard library)

6) build & run
如果报类似于找不到C++标准库的头文件的编译错误,
需要手动添加obfuscator的build目录中include/c++目录,
$ cd /path/to/obfuscator_include	# 例如build/include
$ ln -s /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/ c++

7) 手动设置ollvm-clang的路径
点击项目图标:
	菜单: Editor
		-> Add Build Setting
			-> Add User-Defined Setting
	将NEW_SETTING改成CC, value里填/path/to/obfuscator_bin/clang
可以同样方式增加CXX来指定c++编译器

8) 在CMake里自动设置编译器
set_target_properties(your-target PROPERTIES XCODE_ATTRIBUTE_CC "${YOUR_CC}")
set_target_properties(your-target PROPERTIES XCODE_ATTRIBUTE_CXX "${YOUR_CXX}")
参考:
https://stackoverflow.com/questions/39327952/how-can-i-force-xcode-to-use-a-custom-compiler

9) 替换xcode默认clang为ollvm-clang
$ cd /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
$ mv clang clang.backup
$ ln -s /path/to/obfuscator_bin/clang clang

10) 在CMake里自动设置编译器选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mllvm -fla")
