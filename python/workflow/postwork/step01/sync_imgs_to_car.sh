#!/bin/bash

function is_not_empty_dir()
{
    local test_dir=$1
    if [ ! -e "$test_dir" ]
    then
        echo "$test_dir is no exists"
        return 1
    fi
    
    if [ ! -d "$test_dir" ]
    then
        echo "$test_dir is no dir"
        return 1
    fi
    
    if [ -z "`ls -A $test_dir`" ]
    then
        echo "$test_dir is empty dir"
        return 1
    fi
    
    echo "$test_dir is dir and not empty"
    return 0
}

function is_valid_dst_mount_dir()
{
    local test_dir=$1
    echo "is_valid_dst_mount_dir(\"${test_dir}\")"
    echo "ls -tlr \"${test_dir}\""
    ls -tlr "${test_dir}"
    if ! mountpoint -q "$test_dir"
    then
        echo "$test_dir is no an mountpoint"
        return 1
    fi

    if ! ls -1d "${test_dir}"/white-rhino-*
    then
        echo "$test_dir has no white-rhino-* subdir"
        return 1
    fi

    if ! ls -1d "${test_dir}"/imgs
    then
        echo "$test_dir has no imgs subdir"
        return 1
    fi

    echo "$test_dir is dir and no empty"
    return 0
}

src_sync_dir="/gondor/imgs/sync"

if ! is_not_empty_dir "${src_sync_dir}"
then
    echo "check src_sync_dir: ${src_sync_dir} failed, needn't sync imgs"
    exit 1
fi

for dst_mount_dir in /media/*/*
do
    echo "dst_mount_dir is: $dst_mount_dir"
    if ! is_valid_dst_mount_dir "${dst_mount_dir}"
    then
        echo "$dst_mount_dir is not valid mount dir"
        continue
    fi
    echo "sync imgs to $dst_mount_dir"
    rsync -avP --delete "${src_sync_dir}"/ "${dst_mount_dir}"/imgs
done
