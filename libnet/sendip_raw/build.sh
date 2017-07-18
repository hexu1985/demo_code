#!/bin/sh
g++ -g -Wall `libnet-config --defines` sendip_raw.cpp -o sendip_raw `libnet-config --libs`
