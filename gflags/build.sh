mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=~/local \
	-DBUILD_SHARED_LIBS=OFF \
	-DBUILD_STATIC_LIBS=ON \
	-DBUILD_gflags_LIB=ON \
	-DINSTALL_STATIC_LIBS=ON \
	-DINSTALL_SHARED_LIBS=OFF \
	-DREGISTER_INSTALL_PREFIX=OFF ..
cmake --build . --target install --config Release
