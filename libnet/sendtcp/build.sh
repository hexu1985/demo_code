#!/bin/sh
g++ -Wall `libnet-config --defines` sendtcp.cpp -o sendtcp `libnet-config --libs`
