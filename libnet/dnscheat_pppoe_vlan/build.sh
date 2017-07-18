#!/bin/sh
# run dnscheat as root
#g++ -g dnscheat.cpp dns_header.cpp -o dnscheat -lpcap
g++ -g -c -Wall `libnet-config --defines` -DSEND_LOCAL -DNDEBUG dnscheat.cpp
g++ -g -DNDEBUG -c dns_header.cpp
g++ -g -c -Wall `libnet-config --defines` sendudpresp.cpp
g++ dnscheat.o dns_header.o sendudpresp.o -o dnscheat `libnet-config --libs` -lpcap
