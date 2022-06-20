#!/bin/bash

run_secs=10

if (( $# >= 1 ))
then
    run_secs=$1
fi

echo "run for ${run_secs} seconds"

for i in `seq 1 ${run_secs}`
do
    date
    echo "$0 is running..."
    sleep 1
done

exit 0
