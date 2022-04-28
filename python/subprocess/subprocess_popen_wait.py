#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""
"""


#end_pymotw_header
import subprocess
import os


proc = subprocess.Popen(
    "./run_forever.sh"
)

try:
    ret=proc.wait(10)
except subprocess.TimeoutExpired as err:
    print("timeout")
    proc.kill()

