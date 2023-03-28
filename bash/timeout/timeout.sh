#!/bin/bash

function alarm_timeout() {
    echo "timeout"
    exit 1
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
    ./sleep_and_signal.sh $nsec $$ &
    $func
}

trap 'alarm_timeout' 10

timeout 10 xxx
