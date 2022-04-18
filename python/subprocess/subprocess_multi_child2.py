#!/usr/bin/env python3
"""Replacing os.system with subprocess.
"""

#end_pymotw_header
import subprocess
import time
import threading

class MySubprocess:
    def __init__(self, cmd):
        super().__init__()
        self.cmd = cmd

    def run(self):
        self.subprocess = subprocess.Popen(self.cmd, shell=True)

    def wait(self):
        self.subprocess.wait()
        print('returncode:', self.subprocess.returncode)


childs = []
for i in range(5):
    print("start child process {}".format(i))
    t = MySubprocess('./test.sh {}'.format(i))
    childs.append(t)
    t.run()


for child in childs:
    child.wait()

