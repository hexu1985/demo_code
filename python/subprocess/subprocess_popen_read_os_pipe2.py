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

info_in, info_out = os.pipe()

print('read:')
proc = subprocess.Popen(
    './test.sh 2',
    shell=True,
    stdout=info_out,
    stderr=info_out,
    bufsize=1
)
os.close(info_out)
print("info_out: ")
finfo_in = os.fdopen(info_in)
for line in finfo_in:
    line = line.rstrip()
    print("{}".format(line))

proc.wait()
print('after proc')
print('return code: {}'.format(proc.returncode))
