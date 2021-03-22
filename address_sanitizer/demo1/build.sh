#!/usr/bin/env bash
gcc -g -fsanitize=address -fno-omit-frame-pointer -o main main.c
