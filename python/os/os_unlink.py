#!/usr/bin/env python3

import os
import sys

file_to_remove = "/tmp/test.txt"

try:
    os.unlink(file_to_remove)
except:
    print("unlink {} failed".format(file_to_remove))
    print("Unexpected error:", sys.exc_info()[0])
