1、在项目工程目录下生成配置文件
cd test/            #进入项目目录（test为例说明）
doxygen -g        #生成配置文件
提示：
    a.默认生成的配置文件名为 "Doxyfile"，也可以指定生成的配置文件名：doxygen -g your-cfg-filename
    b.可以在生成配置文件的命令中添加 "-s" 选项，生成不含注释的配置文件：doxygen -sg

2、根据需要，修改配置文件
常用选项如下：

# 项目名称，将作为于所生成的程序文档首页标题
PROJECT_NAME        = “Test”
# 文档版本号，可对应于项目版本号，譬如 svn、cvs 所生成的项目版本号
PROJECT_NUMBER      = "1.0.0
# 程序文档输出目录
OUTPUT_DIRECTORY    =  /home/user1/docs
 
# 程序文档输入目录
INPUT                = /home/user1/project/kernel
 
# 程序文档语言环境
OUTPUT_LANGUAGE      = Chinese
 
# 只对头文件中的文档化信息生成程序文档
FILE_PATTERNS        =
 
# 递归遍历当前目录的子目录，寻找被文档化的程序源文件
RECURSIVE            = YES
# 如果是制作 C 程序文档，该选项必须设为 YES，否则默认生成 C++ 文档格式
OPTIMIZE_OUTPUT_FOR_C  = YES
 
#提取信息，包含类的私有数据成员和静态成员
EXTRACT_ALL            = yes
EXTRACT_PRIVATE        = yes
EXTRACT_STATIC        = yes
# 对于使用 typedef 定义的结构体、枚举、联合等数据类型，只按照 typedef
定义的类型名进行文档化
TYPEDEF_HIDES_STRUCT  = YES
# 在 C++ 程序文档中，该值可以设置为 NO，而在 C 程序文档中，由于 C
语言没有所谓的域/名字空间这样的概念，所以此处设置为 YES
HIDE_SCOPE_NAMES      = YES
# 让 doxygen 静悄悄地为你生成文档，只有出现警告或错误时，才在终端输出提示信息
QUIET  = YES
# 递归遍历示例程序目录的子目录，寻找被文档化的程序源文件
EXAMPLE_RECURSIVE      = YES
# 允许程序文档中显示本文档化的函数相互调用关系
REFERENCED_BY_RELATION = YES
REFERENCES_RELATION    = YES
REFERENCES_LINK_SOURCE = YES
# 不生成 latex 格式的程序文档
GENERATE_LATEX        = NO
# 在程序文档中允许以图例形式显示函数调用关系，前提是你已经安装了 graphviz
软件包
HAVE_DOT              = YES
CALL_GRAPH            = YES
CALLER_GRAPH          = YES
#在最后生成的文档中，把所有的源代码包含在其中
SOURCE BROWSER        = YES
$这会在HTML文档中，添加一个侧边栏，并以树状结构显示包、类、接口等的关系
GENERATE TREEVIEW      ＝ ALL
 
3、程序注释文档化
使用Doxygen，需要按照Doxygen 的游戏规则来对程序源码进行文档化。
Doxygen 的注释类型可分为：
1、行间注释：注释语句不与程序源码出现在同一行，主要用于注释头文件中出现的结构体
(struct)、枚举 (enum)、联合 (uion) 等数据类型，以及程序接口的功能与使用约定；
2、行内注释：注释语句与程序源码出现在同一行内，主要用于代码的局部注释。
详细语法参考：http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html
 
4、文档生成
cd test/
doxygen
提示：
可以指定配置文件名：doxygen  your-cfg-filename

5、文档使用
生成的文档位于test/doc/html 目录中，使用浏览器打开该目录中的 index.html
文件，即可看到自己的工作成果。
