#!/bin/sh
g++ -Wall `libnet-config --defines` sendtcp_raw.cpp -o sendtcp_raw `libnet-config --libs`
