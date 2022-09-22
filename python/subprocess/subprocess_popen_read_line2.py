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
    bufsize=1
)
print("stdout: ")
for line in proc.stdout:
    line = line.rstrip()
    print("{}".format(line.decode('utf-8')))
print("stderr: ")
for line in proc.stderr:
    line = line.rstrip()
    print("{}".format(line.decode('utf-8')))
proc.wait()
print('after proc')
print('return code: {}'.format(proc.returncode))
