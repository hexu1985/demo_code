#!/bin/sh
# run printether as root
g++ printether.cpp -o printether -lpcap
g++ printether2.cpp -o printether2 -lpcap
