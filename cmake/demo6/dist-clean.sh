#!/usr/bin/env bash
for dir in src lib
do
    echo $dir
    $(cd $dir && ./dist-clean.sh)
done

rm -rf build Makefile CMakeCache.txt CMakeFiles cmake_install.cmake

