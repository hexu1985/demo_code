#!/usr/bin/env bash

# static lib
g++ -o mynew.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew.cpp
ar rcs libmynew_s.a mynew.o 
g++ -o main.o -c main.cpp -std=c++11
g++ -o main_s main.o -L. -lmynew_s
