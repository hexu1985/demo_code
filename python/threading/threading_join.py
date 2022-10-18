#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""Passing arguments to threads when they are created
"""

#end_pymotw_header
import threading
import time

def worker(num):
    """thread worker function"""
    for i in range(3):
        print('Worker: %s' % num)
        time.sleep(1)
        print('Worker: %s' % num)


threads = []
print("start threading")
for i in range(5):
    t = threading.Thread(target=worker, args=(i,))
    threads.append(t)
    t.start()

time.sleep(1)
print("start join")
for t in threads:
    t.join()

print("after join")
