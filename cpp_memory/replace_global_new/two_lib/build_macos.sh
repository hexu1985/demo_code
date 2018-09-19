#!/usr/bin/env bash

rm -f *.o *.so *.a main main2

# static lib: 
# main.o -> liblib1_s.a, libmynew_s.a
g++ -o main.o -c -std=c++11 main.cpp
g++ -o mynew.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew.cpp
g++ -o lib1.o -c -std=c++11 -fPIC -fvisibility=hidden lib1.cpp
ar rcs liblib1_s.a lib1.o mynew.o 
g++ -o main main.o -L. -llib1_s
ld -arch x86_64 -r -o lib1_all.o lib1.o mynew.o -unexported_symbols_list unexported.symbols.list
ar rsc liblib1_s2.a lib1_all.o 
g++ -o main2 main.o -L. -llib1_s2
