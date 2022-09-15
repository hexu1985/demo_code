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
        completed = subprocess.run(self.cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        print('returncode:', completed.returncode)

if __name__ == "__main__":
    print("start child process")
    t = MySubprocess(['./test.sh', '1'])
    t.start()
    t.join()


