#!/usr/bin/env python

import sys
import os
import os.path

def find_type_f(dir_name):
    if dir_name[-1] == '/':
        dir_name = dir_name[0:-1]
    for path in os.listdir(dir_name):
        abs_path = dir_name + '/' + path
        if (os.path.isfile(abs_path)):
            print("%s" % abs_path)
        if (os.path.isdir(abs_path)):
            find_type_f(abs_path)

if len(sys.argv) != 2:
    print("Usage:", sys.argv[0], "dir")
    raise SystemExit(1)

find_type_f(sys.argv[1])

