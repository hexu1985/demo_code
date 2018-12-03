# android gdbserver调试
1) 将相应架构的 gdbserver 拷贝到 android 机器上去 (可以使用scp 或者 adb push)
2) 编译被调试程序增加-g的选项
3) 将被调试程序拷贝到 android 机器上去
4) 在 android机器上通过gdbserver启动被调试程序:
# gdbserver tcp:5039 </system/bin/executable>
(or)
# gdbserver tcp:5039 --attach <pid>
5039是端口号.
5) 在linux(编译主机)上启动gdbclient:
#./prebuilt/linux-x86_64/bin/gdb
> target remote 10.1.33.66:1024
> b main
> c

6) gdb和gdbserver路径举例:
    - gdb：$NDK_DIR/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-gdb，中间的路径根据自己情况更改。
    - gdbserver：位置：$NDK_DIR/prebuilt/android-arm64/gdbserver
