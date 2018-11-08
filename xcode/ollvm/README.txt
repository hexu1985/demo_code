一、obfuscator-llvm编译
1) 下载项目并编译
$ git clone -b llvm-4.0 https://github.com/obfuscator-llvm/obfuscator.git
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_INCLUDE_TESTS=OFF -DLLVM_CREATE_XCODE_TOOLCHAIN=On -DCMAKE_INSTALL_PREFIX=$PWD/install ../obfuscator/
$ make -j7

