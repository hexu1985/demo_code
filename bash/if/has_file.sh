#!/bin/bash

test_file=$1

if [ ! -e $test_file ]
then
    echo "$test_file not exist!"
fi
