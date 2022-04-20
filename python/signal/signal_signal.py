#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""
"""


#end_pymotw_header
import signal
import os
import time
import logging

LOGGER = logging.getLogger()
logging.basicConfig(level=logging.INFO)


def receive_signal(signum, stack):
    print('Received:', signum)
    LOGGER.info('Received: {}'.format(signum))
    if signum == signal.SIGUSR1:
        LOGGER.info("Received: signal.SIGUSR1")

# Register signal handlers
signal.signal(signal.SIGUSR1, receive_signal)
signal.signal(signal.SIGUSR2, receive_signal)

# Print the process ID so it can be used with 'kill'
# to send this program signals.
print('My PID is:', os.getpid())

while True:
    print('Waiting...')
    time.sleep(3)
