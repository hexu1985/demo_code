#!/bin/bash

### kill workflow_service/main.py
workflow_service_pid=$(ps aux | grep 'workflow_service/[m]ain.py' | awk '{print $2}')
if [ -z "$workflow_service_pid" ]
then
    echo "workflow_service/main.py is not running"
else
    kill -9 "$workflow_service_pid"
fi

### kill uevent_mointor
uevent_monitor_pid=$(ps aux | grep 'uevent_monitor /tmp/[U]eventPublisher.unix.dg' | awk '{print $2}')
if [ -z "$uevent_monitor_pid" ]
then
    echo "uevent_monitor is not running"
else
    kill -9 "$uevent_monitor_pid"
fi
