#!usr/bin/env python3

import sys
import os
import pathlib
import threading
import subprocess
import socket
import time
import datetime
import logging
import signal

LOGGER = logging.getLogger()

def error_exit(msg):
    LOGGER.error(msg)
    os.kill(os.getpid(), signal.SIGKILL)

class Uevent:
    def __init__(self):
        self.action = ""
        self.devpath = ""
        self.subsystem = ""
        self.devname = ""
        self.devtype = ""
        self.timestamp = time.time()

class UeventMonitorProxy(threading.Thread):
    def __init__(self, work_dir, receiver_unix_domain_path):
        super().__init__()
        self.work_dir = work_dir
        self.cmd = [self.get_uevent_monitor_dir()+"/uevent_monitor", receiver_unix_domain_path]
        self.log_path = work_dir+"/log/uevent_monitor.log.%s"%datetime.datetime.now().strftime('%Y%m%d-%H%M%S.%f')
        LOGGER.info('create UeventMonitorProxy(work_dir="{}", receiver_unix_domain_path="{}")'.format(work_dir, receiver_unix_domain_path))

    def run(self):
        try:
            # kill old uevent_monitor
            kill_old = subprocess.run(["bash", self.work_dir+"/kill_uevent_monitor.sh"])
            LOGGER.info('kill_uevent_monitor.sh returncode: {}'.format(kill_old.returncode))

            with open(self.log_path, mode='w') as f:
                # run uevent_monitor
                uevent_monitor = subprocess.run(self.cmd, stdout=f, stderr=f)
                LOGGER.info('uevent_monitor returncode: {}'.format(uevent_monitor.returncode))
        except Exception as err:
            LOGGER.error("UeventMonitorProxy run error: {}".format(err))

        error_exit("uevent_monitor not run or already exit!")

    def get_uevent_monitor_dir(self):
        current_file_path=os.path.dirname(__file__)
        if not current_file_path:
            current_file_path = os.getcwd()
        current_file_path = pathlib.Path(current_file_path).resolve()
        return str(current_file_path)

class UeventMonitorClient:
    def __init__(self, receiver_unix_domain_path):
        self.receiver_unix_domain_path = receiver_unix_domain_path

        if os.path.exists(self.receiver_unix_domain_path):
            os.remove( self.receiver_unix_domain_path )
         
        LOGGER.info("starting unix domain socket server.")
        self.server = socket.socket( socket.AF_UNIX, socket.SOCK_DGRAM )
        self.server.bind(self.receiver_unix_domain_path)
        LOGGER.info('create UeventMonitorClient("{}")'.format(receiver_unix_domain_path))

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
                # print("invalid key: {}".format(key))
                pass

        return uevent

    def receiveUevent(self):
        datagram = self.server.recv( 4096 )
        if not datagram:
            LOGGER.error("receive empty data")
            return None
        return self.toUevent(datagram.decode('ascii'))

class UeventPublisher(threading.Thread):
    def __init__(self, work_dir):
        super().__init__()
        self.observers = []
        self.work_dir = work_dir
        self.unix_domain_path = "/tmp/UeventPublisher.unix.dg"
        LOGGER.info('create UeventPublisher("{}")'.format(work_dir))

    def addObserver(self, observer):
        # 该方法非线程安全, 所以start以后就不能再add了
        if self.is_alive():
            LOGGER.error('thread is running! Failed to add: {}'.format(observer))
            return

        if observer not in self.observers:
            self.observers.append(observer)
        else:
            LOGGER.error('Failed to add: {}'.format(observer))

    def removeObserver(self, observer):
        # 该方法非线程安全, 所以start以后就不能再remove了
        if self.is_alive():
            LOGGER.error('thread is running! Failed to add: {}'.format(observer))
            return

        try:
            self.observers.remove(observer)
        except ValueError:
            LOGGER.error('Failed to remove: {}'.format(observer))

    def notifyAddAction(self, uevent):
        [o.OnUeventAddAction(uevent) for o in self.observers]

    def notifyRemoveAction(self, uevent):
        [o.OnUeventRemoveAction(uevent) for o in self.observers]

    def run(self):
        client = UeventMonitorClient(self.unix_domain_path)
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
                LOGGER.warning("unfocus event type, action: {}".format(uevent.action))


if __name__ == "__main__":
    class DemoUeventObserver:
        def __init__(self):
            pass
    
        def printUevent(self, uevent):
            print("-"*20)
            print("action: {}".format(uevent.action))
            print("devpath: {}".format(uevent.devpath))
            print("subsystem: {}".format(uevent.subsystem))
            print("devname: {}".format(uevent.devname))
            print("devtype: {}".format(uevent.devtype))
            print("timestamp: {}".format(int(uevent.timestamp)))
            print("-"*20)
    
        def OnUeventAddAction(self, uevent):
            print("OnUeventAddAction")
            self.printUevent(uevent)
    
        def OnUeventRemoveAction(self, uevent):
            print("OnUeventRemoveAction")
            self.printUevent(uevent)

    print("uevent_monitor start")
    logging.basicConfig(level=logging.DEBUG)
    CURRENT_FILE_PATH=os.path.dirname(sys.argv[0])
    if not CURRENT_FILE_PATH:
        CURRENT_FILE_PATH = os.getcwd()
    CURRENT_FILE_PATH = pathlib.Path(CURRENT_FILE_PATH).resolve()

    observer = DemoUeventObserver()
    publisher = UeventPublisher(str(CURRENT_FILE_PATH))
    publisher.addObserver(observer)
    publisher.start()
    publisher.join()
