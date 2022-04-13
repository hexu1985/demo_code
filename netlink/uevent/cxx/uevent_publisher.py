#!usr/bin/env python3

import sys
import os
import pathlib
import threading

CURRENT_FILE_PATH=""

class UeventPublisher(threading.Thread):
    __init__(self, work_dir):
        self.observers = []
        self.work_dir = work_dir

    def addObserver(self, observer):
        # 该方法非线程安全, 所以start以后就不能再add了
        if self.is_alive():
            print('thread is running! Failed to add: {}'.format(observer))
            return

        if observer not in self.observers:
            self.observers.append(observer)
        else:
            print('Failed to add: {}'.format(observer))

    def removeObserver(self, observer):
        # 该方法非线程安全, 所以start以后就不能再remove了
        if self.is_alive():
            print('thread is running! Failed to add: {}'.format(observer))
            return

        try:
            self.observers.remove(observer)
        except ValueError:
            print('Failed to remove: {}'.format(observer))

    def notifyAddAction(self):
        [o.OnUeventAddAction(self) for o in self.observers]

    def notifyRemoveAction(self):
        [o.OnUeventRemoveAction(self) for o in self.observers]

    def run(self):


if __name__ == "__main__":
    print("uevent_monitor start")
    CURRENT_FILE_PATH=os.path.dirname(sys.argv[0])
    if not CURRENT_FILE_PATH:
        CURRENT_FILE_PATH = os.getcwd()
    CURRENT_FILE_PATH = pathlib.Path(CURRENT_FILE_PATH).resolve()
