#!/usr/bin/env bash

name='strange'
if (( $# >= 1 ))
then
    name=$1
fi

echo "$$" > $name.txt

while true
do
    data=$(date)
    echo "hello $name: $data" >> $name.txt
    sleep 2
done

