#!/usr/bin/env bash

debug=0
test $debug -gt 0 && echo "shell:$SHELL"

if (( $# != 1 ))
then
    echo "usage: $0 datafile"
    exit 1
fi

datafile=$1
sum=0
tmpfile=/tmp/$datafile.$$
grep -v '^#' $datafile | grep -v '^ *$' > $tmpfile
while read line
do
    tmp=$(echo $line | bc)
    sum=$(echo "$sum+$tmp" | bc)
    test $debug -gt 0 && echo "tmp: $tmp" 
    test $debug -gt 0 && echo "sum: $sum"
done < $tmpfile

rm $tmpfile
test $debug -gt 0 && echo "sum: $sum"
echo $sum
