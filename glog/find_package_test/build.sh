mkdir build
cd build
cmake -Dglog_DIR=~/local/lib/cmake/glog \
    -Dgflags_DIR=~/local/lib/cmake/gflags \
    ..
#cmake -Dgflags_DIR=~/local/lib/cmake/gflags \
#    -Dglog_INCLUDE_DIRS=~/local/include \
#	-Dglog_LIB_DIRS=~/local/lib ..
VERBOSE=1 cmake --build . 
