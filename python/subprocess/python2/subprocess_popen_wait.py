#!/usr/bin/env python
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""
"""


#end_pymotw_header
import subprocess
import os
import time


proc = subprocess.Popen(
    "../run_forever.sh"
)

is_timeout = True
for i in range(1, 11):
    time.sleep(1)
    print("wait for {} secs".format(i))
    ret = proc.poll()
    if ret is not None:
        is_timeout = True
        break

if is_timeout:
    print("timeout")
    proc.kill()

ret = proc.wait()
print("ret: ", ret)
