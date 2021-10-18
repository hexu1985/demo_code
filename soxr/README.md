## 下载编译soxr
```
$ git clone https://github.com/chirlu/soxr.git
$ cd soxr
$ cmake -H. -Bbuild -DBUILD_EXAMPLES=ON #-DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Debug -DWITH_OPENMP=OFF
$ cmake --build build
```

