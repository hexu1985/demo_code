#!/bin/sh

if (( $# != 1))
then
  echo "usage: $0 list_file"
  exit 1
fi

list_file=$1

if [ ! -f "$list_file" ]
then
  echo "$list_file not exists"
  exit 2
fi

cat $list_file | while read line
do
  url=$(echo $line | cut -d' ' -f 1)
  outdir=$(echo $line | cut -d' ' -f 2)-$(date "+%Y%m%d")
  echo $url
  echo $outdir
  ./wget_esf_sina.sh $url $outdir
done
