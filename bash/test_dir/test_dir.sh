#!/bin/bash

echo $#
if [ $# -lt 1 ]
then
    echo "usage $0 dir"
    exit 1
fi

test_dir=$1

if [ ! -e "$test_dir" ]
then
    echo "$test_dir is no exists"
    exit 1
fi

if [ ! -d "$test_dir" ]
then
    echo "$test_dir is no dir"
    exit 1
fi

if [ -z "`ls -A $test_dir`" ]
then
    echo "$test_dir is empty dir"
    exit 1
fi

echo "$test_dir is dir and no empty"
