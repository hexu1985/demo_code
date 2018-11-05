一、创建C++项目
1) 打开Xcode: 
    -> Create a new Xcode project
    -> Choose a template for your new project: 选macOS: Command Line Tool
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

