#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""Using enumerate() to find the active threads.
"""

#end_pymotw_header
import random
import threading
import time
import logging


def worker():
    """thread worker function"""
    for i in range(3):
        logging.debug('sleeping')
        time.sleep(1)
    logging.debug('ending')


logging.basicConfig(
    level=logging.DEBUG,
    format='(%(threadName)-10s) %(message)s',
)

for i in range(3):
    t = threading.Thread(target=worker, daemon=True)
    t.start()

time.sleep(10)

