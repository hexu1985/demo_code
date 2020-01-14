ubuntu下编译glog(glog依赖gflags, gflags编译参考gflags的README.txt):
# git clone https://github.com/google/glog.git
# cd glog
# mkdir build
# cd build
# cmake -DCMAKE_INSTALL_PREFIX=~/local \
    -Dgflags_DIR=~/local/lib/cmake/gflags/ \
    ..
cmake --build . --target install

