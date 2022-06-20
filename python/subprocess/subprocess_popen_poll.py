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
import time


logf = open("log.txt", mode='w')
proc = subprocess.Popen(
    "./run_for_some_secs.sh 50",
    shell=True, 
    stdout=logf
)

while True:
    ret = proc.poll()
    time.sleep(1)
    print("{}: ret={}".format(time.ctime(), ret))

    if ret is not None:
        break

