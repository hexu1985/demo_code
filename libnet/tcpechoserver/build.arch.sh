#!/bin/sh
# run httpredirect as root
#g++ -g -c -DSEND_LOCAL -Wall `libnet-config --defines` tcpechoserver.cpp
g++ -g -c -Wall `libnet-config --defines` tcpechoserver.cpp
g++ -g -c -Wall `libnet-config --defines` sendtcpresp.cpp
g++ -g -c -Wall `libnet-config --defines` sendtcpack.cpp
g++ -g -c -Wall `libnet-config --defines` sendtcpacksyn.cpp
g++ tcpechoserver.o sendtcpack.o sendtcpacksyn.o sendtcpresp.o -o tcpechoserver `libnet-config --libs` -lpcap
