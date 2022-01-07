#!/usr/bin/env bash

rm -f *.o *.so *.a main

# shared lib: 
# libmylib.so -> liblib1_s.a, liblib2_s.a libmynew_s.a
# main.o -> libmylib.so
g++ -o main.o -c -std=c++11 main.cpp
g++ -o mynew.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew.cpp
ar rcs libmynew_s.a mynew.o 
g++ -o lib1.o -c -std=c++11 -fPIC -fvisibility=hidden lib1.cpp
ar rcs liblib1_s.a lib1.o 
g++ -o lib2.o -c -std=c++11 -fPIC -fvisibility=hidden lib2.cpp
ar rcs liblib2_s.a lib2.o 
g++ -o libmylib.so -shared -L. -Wl,--whole-archive liblib1_s.a -Wl,--whole-archive liblib2_s.a -Wl,--no-whole-archive libmynew_s.a -Wl,--exclude-libs,libmynew_s.a
g++ -o main main.o -L. -lmylib

