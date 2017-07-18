#!/bin/sh
# run dnssniffer as root
#g++ -g dnssniffer.cpp dns_header.cpp -o dnssniffer -lpcap
g++ -DNDEBUG -c dnssniffer.cpp
g++ -DNDEBUG -c dns_header.cpp
g++ -DNDEBUG -c dnssniffer2.cpp
g++ dnssniffer.o dns_header.o -o dnssniffer -lpcap
g++ dnssniffer2.o dns_header.o -o dnssniffer2 -lpcap
