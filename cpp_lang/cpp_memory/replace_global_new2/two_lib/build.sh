#!/usr/bin/env bash

rm -f *.o *.so *.a main main2

# shared lib: 
# libmylib.so -> liblib1_s.a, libmynew_exp.a
# main.o -> libmylib.so libmynew_imp.a
g++ -o main.o -c -std=c++11 main.cpp
g++ -o mynew_imp_default.o -c -std=c++11 ../mynew/mynew_imp_default.cpp
ar rcs libmynew_imp_default.a mynew_imp_default.o 
g++ -o mynew_imp_with_malloc.o -c -std=c++11 ../mynew/mynew_imp_with_malloc.cpp
ar rcs libmynew_imp_with_malloc.a mynew_imp_with_malloc.o 
g++ -o mynew_exp.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew_exp.cpp
ar rcs libmynew_exp.a mynew_exp.o 
g++ -o lib1.o -c -std=c++11 -fPIC -fvisibility=hidden lib1.cpp
ar rcs liblib1_s.a lib1.o 
g++ -o libmylib.so -shared -L. libmynew_exp.a -Wl,--whole-archive liblib1_s.a -Wl,--no-whole-archive libmynew_exp.a -Wl,--exclude-libs,libmynew_exp.a
g++ -o main main.o -L. -lmylib -L. -lmynew_imp_default
g++ -o main2 main.o -L. -lmylib -L. -lmynew_imp_with_malloc

