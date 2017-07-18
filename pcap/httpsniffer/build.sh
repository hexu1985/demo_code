#!/bin/sh
# run httpsniffer as root
g++ -DNDEBUG -c httpsniffer.cpp
g++ -DNDEBUG -c httpsniffer2.cpp
g++ -DNDEBUG -c httpget.cpp
g++ httpsniffer.o httpget.o -o httpsniffer -lpcap
g++ httpsniffer2.o httpget.o -o httpsniffer2 -lpcap
