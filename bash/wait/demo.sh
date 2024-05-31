#!/usr/bin/env bash


echo "sleep begin"
date

sleep 5 &

pid=$!

for i in $(seq 100)
do
    sleep 1
    if kill -0 $pid
    then
        echo "process is alive"
    else
        echo "process is exit"
        break
    fi
done
    
