#!/bin/bash

seq_beg=1647855761

for i in `seq 1 100`
do
    seq=$((seq_beg + 60*i + ${RANDOM}%5))
    echo "dd if=/dev/zero of=/tmp/test.${seq} bs=1M count=1000"
done


