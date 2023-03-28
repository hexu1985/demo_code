#!/bin/bash 
nsec=$1
target_pid=$2
sleep $nsec 
kill -SIGUSR1 $target_pid


