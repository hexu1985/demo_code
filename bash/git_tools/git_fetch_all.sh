#!/bin/sh

echo $0
WORK_DIR=$(dirname $0)
echo $WORK_DIR

git_dir_list=$(find $WORK_DIR -maxdepth 1 -type d | grep -v '^.$')
echo $git_dir_list

for dir in $git_dir_list
do
    (cd $dir && pwd && git fetch --all)
    echo "xxx:" 
    pwd
    echo "yyy:"
done
