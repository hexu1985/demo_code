android 编译openssl
1) clone项目https://github.com/leenjewel/openssl_for_ios_and_android
$ git clone https://github.com/leenjewel/openssl_for_ios_and_android.git
2) 安装ndk: 参考ndk/README.txt
3) clone openssl项目: https://github.com/openssl/openssl.git
4) 编译android版本的openssl
$ cd openssl_for_ios_and_android/tools
$ ./build-openssl4android.sh android64-aarch64 # aarch64
$ ./build-openssl4android.sh android-armeabi   # armv7
5) 注意事项：工具链和openssl库的名字都有要求. 
以e2a39b6f2c2ddbf046ec6ae4dabe77d8b9d11a31的openssl_for_ios_and_android为例
openssl-1.1.0f.tar.gz: openssl库的名字
arm64-v8a-android-toolchain: armv7的工具链要放在tool目录下
armeabi-v7a-android-toolchain: aarch64的工具链要放在tool目录下 

