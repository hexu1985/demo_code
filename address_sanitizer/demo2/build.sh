#!/usr/bin/env bash
g++ -g -fsanitize=address -fno-omit-frame-pointer -std=c++11 -o main main.cpp
