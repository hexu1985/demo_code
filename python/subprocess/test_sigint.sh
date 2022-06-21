#!/bin/bash

trap "echo recv SIGINT; exit 1" SIGINT

while :
do
    echo "$0 is running..."
    sleep 1
done

exit 0
