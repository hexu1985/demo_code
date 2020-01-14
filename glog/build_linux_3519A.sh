rm -rf ./build
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../linux_3519A.cmake \
	-DCMAKE_INSTALL_PREFIX=~/local/linux_3519A \
    -Dgflags_DIR=~/local/lib/cmake/gflags/ \
    ..
cmake --build . --target install --config Release
