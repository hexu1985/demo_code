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
import signal
import time


proc = subprocess.Popen(
    "./test_sigint.sh"
)

time.sleep(5)
print("timeout")
proc.send_signal(signal.SIGINT)
ret = proc.poll()
print('poll ret: {}'.format(ret))
ret = proc.wait()
print('wait ret: {}'.format(ret))

