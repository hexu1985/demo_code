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
err_in, err_out = os.pipe()

print('read:')
proc = subprocess.Popen(
    './test.sh 2',
    shell=True,
    stdout=info_out,
    stderr=err_out,
    bufsize=1
)
os.close(info_out)
os.close(err_out)
print("stdout: ")
finfo_in = os.fdopen(info_in)
for line in finfo_in:
    line = line.rstrip()
    print("{}".format(line))
print("stderr: ")
ferr_in = os.fdopen(err_in)
for line in ferr_in:
    line = line.rstrip()
    print("{}".format(line))

proc.wait()
print('after proc')
print('return code: {}'.format(proc.returncode))
