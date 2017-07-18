#!/bin/sh

g++ -Wall -g -DNDEBUG udp.cpp -o udp 
g++ -Wall -g -DNDEBUG udpechoclient.cpp -o udpechoclient 
g++ -Wall -g -DNDEBUG udpechoserver.cpp -o udpechoserver 
