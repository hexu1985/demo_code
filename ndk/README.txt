一、ndk standalone 安装
1) 下载ndk安装包: 以android-ndk-r14b-linux-x86_64.zip为例
2) unzip android-ndk-r14b-linux-x86_64.zip
3) sudo ./extract_android_toolchain.sh

# 参考文档
https://developer.android.com/ndk/guides/standalone_toolchain?hl=zh-cn

二、obfuscator-llvm ndk安装
1) 下载项目并编译
$ git clone -b llvm-4.0 https://github.com/obfuscator-llvm/obfuscator.git
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_INCLUDE_TESTS=OFF ../obfuscator/
$ make -j7

2) 创建android ndk独立工具链
$ cd android-ndk-r14b/toolchains
# 备份llvm文件夹
# llvm/prebuilt/linux-x86_64/bin下所有文件、文件夹换成1步骤中build/bin
# llvm/prebuilt/linux-x86_64/lib下所有文件、文件夹换成1步骤中build/lib
# 然后按照"一、ndk standalone 安装"步骤安装

# 参考文档
https://blog.csdn.net/tabactivity/article/details/81262570
https://blog.csdn.net/huang_yx005/article/details/76636219
