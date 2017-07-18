#!/bin/sh
g++ -g -Wall `libnet-config --defines` senddns.cpp -o senddns `libnet-config --libs`
