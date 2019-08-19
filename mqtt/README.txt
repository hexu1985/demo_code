
paho.mqtt.cpp
https://github.com/eclipse/paho.mqtt.cpp.git
# branch master
# commit id 0874b245be971d7d034d23e4cebf0a8d9f688f2e

paho.mqtt.c
https://github.com/eclipse/paho.mqtt.c.git
# branch v1.3.1
# commit id d34c51214f4172f2e12bb17532c9f44f72a57dd4

# how to install paho lib
$ sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui

# build and install the Paho C library:
$ git clone https://github.com/eclipse/paho.mqtt.c.git
$ cd paho.mqtt.c
$ git checkout v1.2.1
$ cmake -Bbuild -H. -DPAHO_WITH_SSL=ON
$ sudo cmake --build build/ --target install
$ sudo ldconfig

$ git clone https://github.com/eclipse/paho.mqtt.cpp
$ cd paho.mqtt.cpp
$ cmake -Bbuild -H. -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
# -DCMAKE_PREFIX_PATH=../../paho.mqtt.c/build/install/usr/local ..
$ sudo cmake --build build/ --target install
