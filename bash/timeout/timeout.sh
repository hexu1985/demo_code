#!/bin/bash

function alarm_timeout() {
    echo "timeout"
    exit 1
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

timeout 10 xxx
