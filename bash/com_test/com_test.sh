#!/usr/bin/env bash

if [[ $# == 1 && ( "$1" == "OK" || "$1" == "ok" ) ]]
then
    echo OK
else
    echo ERROR
fi

if [ $# == 1 -a \( "$1" == "OK" -o "$1" == "ok" \) ]
then
    echo OK
else
    echo ERROR
fi

