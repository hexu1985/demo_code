#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""Multiple concurrent access to a resource
"""
#end_pymotw_header
import logging
import random
import threading
import time


def worker(s):
    name = threading.current_thread().getName()
    logging.debug('woker {} is working...'.format(name))
    time.sleep(random.randint(1, 3))
    logging.debug('woker {} is done'.format(name))
    s.release()


logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s (%(threadName)-2s) %(message)s',
)

s = threading.Semaphore(0)
for i in range(4):
    t = threading.Thread(
        target=worker,
        name=str(i),
        args=(s, ),
    )
    t.start()

logging.debug("waiting for worker complete")
for i in range(4):
    s.acquire()
logging.debug("all worker complete")
