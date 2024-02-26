### Google benchmark编译安装

google/benchmark基于c++11标准和googletest框架，所以安装前需要先做一些准备工作。

首先是安装g++和cmake。

- Debian/Ubuntu:

    ```
    $ sudo apt install g++ cmake
    ```

- Arch Linux/Manjaro Linux:

    ```
    $ sudo pacman -s g++ cmake
    ```

然后是googletest框架，你可以选择单独安装，不过这里我选择将其作为benchmark源码树的依赖而不单独安装它，因为benchmark在编译安装时需要googletest但是在使用时并不需要，为了篇幅我们选择后者。

准备工作完成后选择一个合适的目录，然后运行下面的命令：

clone项目:

```
$ git clone https://github.com/google/benchmark.git

$ git clone https://github.com/google/googletest.git benchmark/googletest
```

编译项目

```
$ mkdir build && cd build

$ cmake -DCMAKE_BUILD_TYPE=RELEASE ../benchmark

$ make -j4
```

如果想全局安装就接着运行下面的命令

```
sudo make install
```

头文件会被安装至/usr/local/include，库文件会安装至/usr/local/lib。

现在安装完成了，我们来看看benchmark如何使用。

### 参考资料：

- [Google benchmark入门到精通系列链接](https://zhuanlan.zhihu.com/p/492920760)
- [Google benchmark User Guide](https://google.github.io/benchmark/user_guide.html)
