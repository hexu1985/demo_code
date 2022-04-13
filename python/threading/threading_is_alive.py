#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""Subclassing Thread to create your own thread types.
"""

#end_pymotw_header
import threading
import logging
import time


class MyThread(threading.Thread):

    def run(self):
        while True:
            logging.debug('running')
            time.sleep(3.0)


logging.basicConfig(
    level=logging.DEBUG,
    format='(%(threadName)-10s) %(message)s',
)

if __name__ == "__main__":
    t = MyThread()
    print("t is_alive before start: {}".format(t.is_alive()))
    t.start()
    print("t is_alive after start: {}".format(t.is_alive()))
