#!/usr/bin/env python3
"""Basic sched example
"""

#end_pymotw_header
import sched
import time

scheduler = sched.scheduler(time.time, time.sleep)


def print_event():
    print("{}: hello world!".format(time.ctime()))


start = time.time()
print('START:', time.ctime(start))
scheduler.enter(2, 1, print_event)
scheduler.enter(3, 1, print_event)

scheduler.run()
