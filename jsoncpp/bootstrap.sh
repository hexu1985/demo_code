#!/usr/bin/env bash

# https://github.com/open-source-parsers/jsoncpp/archive/master.zip
git clone https://github.com/open-source-parsers/jsoncpp.git
cd jsoncpp
mkdir build
cd build
#cmake -G"Unix Makefiles" ..    # mingw use g++
cmake ..
make
