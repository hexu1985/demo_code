#!/usr/bin/python
# File name: process_oper_test1.py
# Description: some process operations
# Created on:  2018-07-19
# Author: liitdar
 
import psutil
import os
import signal
 
print("----------------------------- show all processes info --------------------------------")
# show processes info
pids = psutil.pids()
for pid in pids:
    p = psutil.Process(pid)
    # get process name according to pid
    process_name = p.name()
    
    print("Process name is: %s, pid is: %s" %(process_name, pid))
 
print("----------------------------- kill specific process --------------------------------")
pids = psutil.pids()
for pid in pids:
    p = psutil.Process(pid)
    # get process name according to pid
    process_name = p.name()
    # kill process "sleep_test1"
    if 'sleep_test1' == process_name:
        print("kill specific process: name(%s)-pid(%s)" %(process_name, pid))
        os.kill(pid, signal.SIGKILL)
    
exit(0)
