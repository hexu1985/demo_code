#!/bin/sh
g++ -g -Wall `libnet-config --defines` sendudp_raw.cpp -o sendudp_raw `libnet-config --libs`
