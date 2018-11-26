#!/usr/bin/env bash

rm -rf ./build
mkdir ./build
cd build
TARGET_OS=linux cmake ..
make
