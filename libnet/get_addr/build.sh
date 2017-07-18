#!/bin/sh
g++ -g -Wall `libnet-config --defines` get_addr.cpp -o get_addr `libnet-config --libs`
