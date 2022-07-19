#!/usr/bin/env python3

import os
import pathlib

current_path = os.path.abspath(__file__)
current_file_path = pathlib.Path(__file__).resolve()

print("current_path of test.py is {}".format(current_path))
print("current_file_path of test.py is {}".format(current_file_path))
