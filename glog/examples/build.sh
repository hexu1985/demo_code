mkdir build
cd build
cmake -Dglog_INCLUDE_DIRS=~/local/include \
	-Dglog_LIB_DIRS=~/local/lib ..
VERBOSE=1 cmake --build . 
