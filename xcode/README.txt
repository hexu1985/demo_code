一、创建C++项目
1) 打开Xcode: 
    -> Create a new Xcode project
    -> Choose a template for your new project: 选macOS/Application: Command Line Tool
    -> Choose options for your new project:
        -> Product Name: 自己输入
        -> Organization Identifier: 自己输入
        -> Language: 选C++
2) 编辑代码
3) build & run
4) 修改编译target目录:
    -> File -> Project Settings:
            -> Shared Project Settings:
                -> Derived Data: 选择 Project-relative Location
生成的可执行文件放在项目目录的DerivedData/$Project/Build/Products/Debug(Release)下

二、创建C++静态库
1) 打开Xcode: 
    -> Create a new Xcode project
    -> Choose a template for your new project: 选macOS/Framework & Library: Library
    -> Choose options for your new project:
        -> Product Name: 自己输入
        -> Organization Identifier: 自己输入
        -> Framework: STL(C++ Library)
        -> Type: Static
2) 编辑代码
3) build
4) 修改编译target目录:
    -> File -> Project Settings:
            -> Shared Project Settings:
                -> Derived Data: 选择 Project-relative Location
生成的静态库文件放在项目目录的DerivedData/$Project/Build/Products/Debug(Release)下

三、使用C++静态库
前三步同"一、创建C++项目"
但由于缺少第三方lib和头文件, 项目构建肯定会失败
4) 增加头文件搜索路径(等价于makefile中的-Iinclude_dir):
点击项目图标:
    -> Build Settings: 选择All和Combined,
        -> Search Paths:
            -> Header Search Paths: 输入项目依赖的头文件路径
5) 增加链接第三方静态库:
点击项目图标:
    -> Build Settings: 选择General
        -> Linked Frameworks and Libraries: 点击"+", 将依赖库选择进来
6) 再次build & run
