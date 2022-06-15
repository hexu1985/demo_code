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
from functools import partial


def worker(name):
    """thread worker function"""
    for i in range(3):
        logging.debug('{} sleeping'.format(name))
        time.sleep(1)
    logging.debug('{} ending'.format(name))


logging.basicConfig(
    level=logging.DEBUG,
    format='(%(threadName)-10s) %(message)s',
)

for i in range(3):
    t = threading.Thread(target=partial(worker,i), daemon=True)
    t.start()

time.sleep(10)

