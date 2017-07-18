#!/bin/sh
gcc -fPIC -c first.c second.c
gcc -shared first.o second.o -o libstaticlib.so
