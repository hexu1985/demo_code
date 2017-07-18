#!/bin/sh
g++ -g -Wall `libnet-config --defines` sendarp.cpp -o sendarp `libnet-config --libs`
