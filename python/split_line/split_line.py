#!/usr/bin/env python3

import sys

with open(sys.argv[1], 'r') as f:
    for line in f.readlines():
        lines = line.split()
        for i in lines:
            print(i)
        print('\n\n')
