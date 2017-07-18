#!/bin/sh
# run httpredirect as root
g++ -g -c -Wall -D_BSD_SOURCE -D__BSD_SOURCE -D__FAVOR_BSD -DHAVE_NET_ETHERNET_H tcpechoserver.cpp
g++ -g -c -Wall -D_BSD_SOURCE -D__BSD_SOURCE -D__FAVOR_BSD -DHAVE_NET_ETHERNET_H sendtcpresp.cpp
g++ -g -c -Wall -D_BSD_SOURCE -D__BSD_SOURCE -D__FAVOR_BSD -DHAVE_NET_ETHERNET_H sendtcpack.cpp
g++ -g -c -Wall -D_BSD_SOURCE -D__BSD_SOURCE -D__FAVOR_BSD -DHAVE_NET_ETHERNET_H sendtcpacksyn.old.cpp
g++ tcpechoserver.o sendtcpack.o sendtcpacksyn.old.o sendtcpresp.o -o tcpechoserver -lnet -lpcap
