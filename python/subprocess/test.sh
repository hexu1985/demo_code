#!/bin/bash

for i in `seq 1 3`
do
    echo "$0-$1 is running..."
    echo "$0-$1 is error..." >&2
    sleep 1
done

echo "error message" >&2
exit 12
