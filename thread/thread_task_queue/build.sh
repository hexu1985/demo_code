#!/bin/sh

g++ -std=c++11 -c thread.cc
g++ -std=c++11 -c thread_test.cc
g++ -o test thread.o thread_test.o -lpthread
