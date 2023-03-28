#!/bin/bash


function alarm_timeout() {
    echo "timeout"
    stop_flag=1
#    exit 1
}

function sleep_and_signal() {
    local nsec=$1
    local target_pid=$2
    sleep $nsec 
    kill -SIGUSR1 $target_pid
}

function xxx() {
    while true
    do
        if (( stop_flag == 1 ))
        then
            stop_flag=0
            return
        fi
        echo $$
        sleep 1
    done
}

function timeout() {
    local nsec=$1
    func=$2
    sleep_and_signal $nsec $$ &
    $func
}

trap 'alarm_timeout' 10

stop_flag=0
timeout 10 xxx
echo "after timeout"
