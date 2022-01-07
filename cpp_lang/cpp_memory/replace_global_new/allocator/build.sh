#!/usr/bin/env bash

# use default new and delete
g++ -c -std=c++11 allocator.cpp
g++ -o allocator allocator.o

# use mynew.cpp's new and delete
g++ -o mynew.o -c -std=c++11 -fvisibility=hidden ../mynew/mynew.cpp
ar rcs libmynew_s.a mynew.o 
g++ -o allocator_mynew allocator.o -L. -lmynew_s
