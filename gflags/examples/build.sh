mkdir build
cd build
cmake -Dgflags_INCLUDE_DIRS=~/local/include \
	-Dgflags_LIB_DIRS=~/local/lib ..
VERBOSE=1 cmake --build . 
