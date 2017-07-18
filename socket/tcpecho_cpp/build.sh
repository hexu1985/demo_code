#!/bin/sh

#g++ -Wall -g -DNDEBUG tcp.cpp -o tcp 
g++ -Wall -g -O0 -DNDEBUG tcpechoclient.cpp -o tcpechoclient 
g++ -Wall -g -O0 -DNDEBUG tcpechoclient_local.cpp -o tcpechoclient_local
g++ -Wall -g -O0 -DNDEBUG tcpechoserver.cpp -o tcpechoserver 
