#!/usr/bin/env bash

if (( $# != 1 ))
then
    echo "usage: $0 command"
    exit 1
fi

command_str="$1"

while true
do
    eval "nohup $command_str &"
    child_pid="$!"
    echo "sub pid: " $child_pid
    while true
    do
        if kill -0 $child_pid
        then
            echo "$command_str is alive"
            sleep 1
        else
            echo "$command_str is dead"
            break
        fi
    done
done
