#!/bin/sh
# run ipsniffer as root
g++ -g ipsniffer.cpp -o ipsniffer -lpcap
g++ -g ipsniffer2.cpp -o ipsniffer2 -lpcap
