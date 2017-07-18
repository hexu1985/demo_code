#!/usr/bin/env python

import sys
import os
import os.path

def print_dir(dir_name):
    if dir_name[-1] == '/':
        dir_name = dir_name[0:-1]
    for path in os.listdir(dir_name):
        abs_path = dir_name + '/' + path
        print(abs_path)
        if (os.path.isdir(abs_path)):
            print_dir(abs_path)

if len(sys.argv) != 2:
    print("Usage:", sys.argv[0], "dir")
    raise SystemExit(1)

print_dir(sys.argv[1])

