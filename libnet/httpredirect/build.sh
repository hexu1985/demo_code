#!/bin/sh
# run httpredirect as root
g++ -g -c -Wall `libnet-config --defines` -DNDEBUG httpredirect.cpp
g++ -g -c -Wall `libnet-config --defines` sendtcpresp.cpp
g++ -g -DNDEBUG -c httpget.cpp
g++ httpredirect.o httpget.o sendtcpresp.o -o httpredirect `libnet-config --libs` -lpcap
