cmake -G "Visual Studio 14" -Bbuild -H. -DCMAKE_INSTALL_PREFIX="D:\mqtt\x86\mqtt-rpc-client" -DPAHO_WITH_SSL=ON -DPAHO_C_ROOT_DIR="D:\mqtt\x86\paho-c" -DPAHO_CPP_ROOT_DIR="D:\mqtt\x86\paho-cpp" -DOPENSSL_SEARCH_LIB_PATH="C:\OpenSSL-Win32\lib"
cmake --build build/ --target install

