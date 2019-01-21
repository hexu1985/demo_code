1) 查看hello的依赖库
readelf -d hello
2) clang编译可执行程序, 默认链接的是libstdc++.so, 通过指定-static-libstdc++选择libstdc++.a
