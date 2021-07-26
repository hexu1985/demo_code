#!/usr/bin/env bash

rm -rf ./build
mkdir ./build
cd build
# windows
# cmake -G"Unix Makefiles" -DTARGET_OS=windows ..
cmake -DTARGET_OS=linux ..
make
