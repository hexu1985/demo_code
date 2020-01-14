mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=~/local \
    -Dgflags_DIR=~/local/lib/cmake/gflags/ \
    ..
cmake --build . --target install
