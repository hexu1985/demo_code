#!/bin/sh
# run httpblock as root
g++ -g -c -Wall `libnet-config --defines` httpblock.cpp
g++ -g -c -Wall `libnet-config --defines` sendtcprst.cpp
g++ -g -DNDEBUG -c httpget.cpp
g++ httpblock.o httpget.o sendtcprst.o -o httpblock `libnet-config --libs` -lpcap
