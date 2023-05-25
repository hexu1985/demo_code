#!/bin/bash

function is_routing_running() {
    count=$(ps -eaf | grep 'mainboard.*routing\.dag' | wc -l)
    return $count
}

is_routing_running
ret=$?
echo "ret: $ret"
if (( ret > 0 ))
then
    echo "routing is running"
else
    echo "routing is not run"
fi
