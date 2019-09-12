cmake -G "Visual Studio 14 Win64" -Bbuild -H. -DPAHO_WITH_SSL=ON -DCMAKE_INSTALL_PREFIX="D:\mqtt\x64\mqtt-rpc-client" -DPAHO_C_ROOT_DIR="D:\mqtt\x64\paho-c" -DPAHO_CPP_ROOT_DIR="D:\mqtt\x64\paho-cpp" -DOPENSSL_SEARCH_LIB_PATH="C:\OpenSSL-Win64\lib"
cmake --build build/ --target install

