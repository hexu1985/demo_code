#!/usr/bin/env bash

rm -f *.o *.so *.a main

# shared lib: main.o -> liblib1.so -> libmynew.so
g++ -o main.o -c -std=c++11 main.cpp
g++ -o mynew.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew.cpp
g++ -o libmynew.so -shared mynew.o 
g++ -o lib1.o -c -std=c++11 -fPIC -fvisibility=hidden lib1.cpp
g++ -o liblib1.so -shared lib1.o -L. libmynew.so -Wl,--exclude-libs,libmynew.so
g++ -o main main.o -L. -llib1

