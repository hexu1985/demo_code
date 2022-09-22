#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""
"""


#end_pymotw_header
import subprocess

print('read:')
proc = subprocess.Popen(
    './test.sh 2',
    shell=True,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
)
print('after proc')
stdout_value, stderr_value = proc.communicate()
print('stdout:', repr(stdout_value.decode('utf-8')))
print('stderr:', repr(stderr_value.decode('utf-8')))
