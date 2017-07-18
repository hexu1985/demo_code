#!/bin/sh
g++ -g -Wall `libnet-config --defines` sendip.cpp -o sendip `libnet-config --libs`
