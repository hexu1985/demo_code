#!/usr/bin/env python3

import os
import sys
import pathlib

def get_current_file_path():
    current_file_path=os.path.dirname(sys.argv[0])
    if not current_file_path:
        current_file_path = os.getcwd()
    current_file_path = pathlib.Path(current_file_path).resolve()
    return str(current_file_path)

print("os.getcwd():", os.getcwd())
print("__file__:", __file__)
print("sys.argv[0]:", sys.argv[0])
print("get_current_file_path:", get_current_file_path())
