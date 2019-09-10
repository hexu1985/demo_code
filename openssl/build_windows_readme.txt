OpenSSL 1.1 windows编译

第一步下载:https://www.openssl.org/source/ 找到1.1的,下好解压

第二步下载:https://www.activestate.com/activeperl 下好对应版本然后安装

第三步下载:http://www.nasm.us/pub/nasm/releasebuilds/?C=M;O=D 推荐找不带"rc"的下载,这玩意不会自己加环境变量需要手动把它的路径加进PATH

第三步:从开始里找到vs的命令提示,vs2017的叫"适用于 VS 2017 的 x64 本机工具命令提示",vs2008的叫"Visual Studio 2008 x64 Win64 命令提示",如果要编X86的就去启动X86版。

第四步:定位到OpenSSL的源码目录(第一步解压的地方)

第五步:以下多选一

    输入"perl configure VC-WIN64A" 这样生成的是DLL,文件在第一步解压的目录中
    输入"perl configure VC-WIN64A --prefix=D:\OpenSSL\x64" 这样生成的是DLL,文件在D:\OpenSSL\x64
    输入"perl configure VC-WIN64A no-shared --prefix=D:\OpenSSL\x64"这样生成的是静态LIB,文件在D:\OpenSSL\x64
    若需要x86的就把上面VC-WIN64A换成VC-WIN32,这里的A带表AMD64,还有个选项VC-WIN64I对应IA64

第六步:输入"nmake"

第七步:等->死等

第八步:输入"nmake install",执行完就把include和lib给放到prefix指定的目录中了

注意:

    编译过X64后再编译X86需要先nmake clean静态编译的库在使用时需要添加额外链接库:WS2_32.LIB;GDI32.LIB;ADVAPI32.LIB;CRYPT32.LIB;USER32.LIB动态库会依赖VC运行时,比较蛋疼.