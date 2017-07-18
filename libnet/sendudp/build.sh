#!/bin/sh
g++ -g -Wall `libnet-config --defines` sendudp.cpp -o sendudp `libnet-config --libs`
