#!/usr/bin/env python3
"""Replacing os.system with subprocess.
"""

#end_pymotw_header
import subprocess
import time
import threading

class MySubprocess(threading.Thread):
    def __init__(self, cmd):
        super().__init__()
        self.cmd = cmd

    def run(self):
        completed = subprocess.run(self.cmd)
        print('returncode:', completed.returncode)

childs = []
for i in range(5):
    print("start child process {}".format(i))
    t = MySubprocess(['./test.sh', str(i)])
    childs.append(t)
    t.start()


for child in childs:
    child.join()

