#!/usr/bin/env bash

rm -f *.o *.so *.a main

# shared lib: main.o -> liblib1.so, liblib2.so -> libmynew_s.a
g++ -o main.o -c -std=c++11 main.cpp
g++ -o mynew.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew.cpp
ar rcs libmynew_s.a mynew.o 
g++ -o lib1.o -c -std=c++11 -fPIC -fvisibility=hidden lib1.cpp
g++ -o liblib1.so -shared lib1.o -L. libmynew_s.a -Wl,--exclude-libs,libmynew_s.a
g++ -o lib2.o -c -std=c++11 -fPIC -fvisibility=hidden lib2.cpp
g++ -o liblib2.so -shared lib2.o 
g++ -o main main.o -L. -llib1 -llib2

