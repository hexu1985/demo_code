#!usr/bin/env python3

import sys
import os
import pathlib
import threading
import subprocess

CURRENT_FILE_PATH=""

def error_exit(msg):
    print(msg)
    os.kill(os.getpid(), signal.SIGKILL)

class Uevent:
    def __init__(self):
        self.action = ""
        self.devpath = ""
        self.subsystem = ""
        self.devname = ""
        self.devtype = ""

class UeventMonitorProxy(threading.Thread):
    def __init__(self, work_dir, receiver_unix_domain_path):
        super().__init__()
        self.work_dir = work_dir
        self.cmd = [work_dir+"/uevent_monitor", receiver_unix_domain_path]

    def run(self):
        completed = subprocess.run(self.cmd)
        print('returncode:', completed.returncode)
        error_exit("uevent_monitor already exit!")

class UeventMonitorClient:
    def __init__(self, receiver_unix_domain_path):
        self.receiver_unix_domain_path = receiver_unix_domain_path

        if os.path.exists(self.receiver_unix_domain_path):
            os.remove( self.receiver_unix_domain_path )
         
        print("starting unix domain socket server.")
        self.server = socket.socket( socket.AF_UNIX, socket.SOCK_DGRAM )
        self.server.bind(self.receiver_unix_domain_path)

    def toUevent(self, msg): 
        uevent = Uevent()

        lines=msg.split('\n')
        for line in lines:
            key, value = line.split('=')
            if key == "action":
                uevent.action = value
            elif key == "devpath":
                uevent.devpath = value
            elif key == "subsystem":
                uevent.subsystem = value
            elif key == "devname":
                uevent.devname = value
            elif key == "devtype":
                uevent.devtype = value
            else:
                print("invalid key: {}".format(key))

        return uevent

    def receiveUevent(self):
        datagram = server.recv( 4096 )
        if not datagram:
            print("receive empty data")
            return None
        return self.toUevent(datagram.decode('ascii'))

class UeventPublisher(threading.Thread):
    def __init__(self, work_dir):
        self.observers = []
        self.work_dir = work_dir
        self.unix_domain_path = "/tmp/UeventPublisher."+str(os.getpid())

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

    def notifyAddAction(self, uevent):
        [o.OnUeventAddAction(self, uevent) for o in self.observers]

    def notifyRemoveAction(self, uevent):
        [o.OnUeventRemoveAction(self, uevent) for o in self.observers]

    def run(self):
        client = UeventMonitorClient()
        proxy = UeventMonitorProxy(self.work_dir, self.unix_domain_path)
        proxy.setDaemon(True)
        proxy.start()

        while True:
            uevent = client.receiveUevent()
            if uevent.action == 'add':
                self.notifyAddAction(uevent)
            elif uevent.action == 'remove':
                self.notifyRemoveAction(uevent)
            else:
                print("unfocus event type, action: {}".format(uevent.action))


if __name__ == "__main__":
    print("uevent_monitor start")
    CURRENT_FILE_PATH=os.path.dirname(sys.argv[0])
    if not CURRENT_FILE_PATH:
        CURRENT_FILE_PATH = os.getcwd()
    CURRENT_FILE_PATH = pathlib.Path(CURRENT_FILE_PATH).resolve()
