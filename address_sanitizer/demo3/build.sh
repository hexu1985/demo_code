#!/usr/bin/env bash
g++ -g -fsanitize=address -fno-omit-frame-pointer -o main main.cpp
