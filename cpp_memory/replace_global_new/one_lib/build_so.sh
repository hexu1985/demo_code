#!/usr/bin/env bash

# shared lib
g++ -o main.o -c main.cpp -std=c++11
g++ -o mynew.o -c -std=c++11 -fPIC -fvisibility=hidden ../mynew/mynew.cpp
g++ -o libmynew.so -shared mynew.o 
g++ -o main main.o -L. -lmynew

