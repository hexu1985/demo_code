概述
　　Linux 平台上的usb驱动开发，主要有内核驱动的开发和基于libusb的无驱设计。libusb是一个C库，提供对USB设备的通用访问。通过他来进行无驱的USB设备访问控制。
支持哪些平台
　　 Linux，OS X，Windows，Windows CE，Android，OpenBSD 
官方文档
　　http://libusb.info/
代码路径
　　https://github.com/libusb/libusb
依赖库
　　libudev-dev
Debian下编译和安装过程
　　1、首先从github上下载源代码。到本地，或者下载zip包，解压到本地。
　　　　 git clone https://github.com/libusb/libusb.git  
　　2、安装这个库需要依赖autoreconf工具，所以在执行之前先查看是否安装了autoreconf。
　　　　 which autoreconf 

　　　　如果没有安装需要执行如下命令安装autoreconf工具。

　　　　 apt-get install dh-autoreconf 
　　3、安装成功后，直接执行./autogen.sh脚本。
　　　　脚本执行过程中会提示一些未安装的依赖库，比如：libudev库。如果脚本报错退出，按照错
　　误提示，安装所需要的依赖库。
　　　　 apt-get install libudev-dev 
　　4、直接在libusb目录下执行make。等待编译完成。
　　5、编译完成后，进入libusb/.libs/下会生成libusb-1.0.a 和 libusb-1.0.so.0.1.0的文件。
