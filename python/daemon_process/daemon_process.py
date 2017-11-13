#!/usr/bin/env python

import time
import subprocess
import multiprocessing

class DaemonProcess:
    def __init__(self, cmd_str):
        self.cmd_str = cmd_str

    def daemon(self):
        print("daemon before subprocess.call('%s')" % self.cmd_str)
        ret = subprocess.call(self.cmd_str, shell=True)
        print("daemon after subprocess.call('%s'), ret=%s" % (self.cmd_str, ret))

    def run(self, cmd_str=''):
        if len(cmd_str) != 0:
            self.cmd_str = cmd_str
        self.p = multiprocessing.Process(target=self.daemon)
        self.p.daemon = True
        self.p.start()

    def is_alive(self):
        return self.p.is_alive()

    def join(self):
        self.p.join()


if __name__ == '__main__':
    d = DaemonProcess('./test.sh hexu')
    d.run()
    while True:
        if d.is_alive():
            time.sleep(1)
        else:
            d.join()
            time.sleep(0.5)
            d.run()


