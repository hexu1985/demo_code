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

my_env = os.environ.copy()
my_env['DISK_PATH_TEST'] = 'abc'
proc = subprocess.Popen(
    "./test_env.sh",
    shell=True,
    env=my_env
)
proc.wait()
