cmake -Bbuild -H. -DCMAKE_INSTALL_PREFIX="/home/hexu/opt/mqtt-rpc-client" -DPAHO_WITH_SSL=ON -DPAHO_C_ROOT_DIR="/home/hexu/opt/paho-c" -DPAHO_CPP_ROOT_DIR="/home/hexu/opt/paho-cpp" -DOPENSSL_SEARCH_LIB_PATH="/usr/lib/x86_64-linux-gnu"
cmake --build build/ --target install

