#!/bin/bash

uevent_monitor_pid=$(ps aux | grep 'uevent_monitor /tmp/[U]eventPublisher.unix.dg' | awk '{print $2}')
if [ -z "$uevent_monitor_pid" ]
then
    echo "uevent_monitor is not running"
else
    kill -9 "$uevent_monitor_pid"
fi
