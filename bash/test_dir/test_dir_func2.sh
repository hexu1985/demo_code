#!/bin/bash

function check_dir_valid()
{
    local test_dir=$1
    if [ ! -e "$test_dir" ]
    then
        echo "$test_dir is no exists"
        return 0
    fi
    
    if [ ! -d "$test_dir" ]
    then
        echo "$test_dir is no dir"
        return 0
    fi
    
    if [ -z "`ls -A $test_dir`" ]
    then
        echo "$test_dir is empty dir"
        return 0
    fi
    
    echo "$test_dir is dir and not empty"
    return 1
}

echo $#
if [ $# -lt 1 ]
then
    echo "usage $0 dir"
    exit 1
fi

check_dir_valid $1
is_valid=$?
if (( is_valid ))
then
    echo "test_dir $1 ok, is dir and empty"
else
    echo "test_dir $1 fail"
fi

