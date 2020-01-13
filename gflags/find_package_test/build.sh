mkdir build
cd build
cmake -Dgflags_DIR=~/local/lib/cmake/gflags ..
VERBOSE=1 cmake --build . 
