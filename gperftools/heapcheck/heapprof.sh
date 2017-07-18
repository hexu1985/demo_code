#!/usr/bin/env bash

#set -x

function usage {
    echo "usage: $0 program args"
    exit 1
}

if [ $# -eq 0 ]; then
    usage
fi

# the profiler file
PROFILE_DIR=./tmp

EXE_FILE_NAME=`basename $1`

if [ ! -d $PROFILE_DIR ]; then
    mkdir $PROFILE_DIR
fi

export PPROF_PATH=$(which pprof)
env HEAPPROFILE=$PROFILE_DIR/$EXE_FILE_NAME HEAPCHECK=normal LD_PRELOAD="/usr/lib/libtcmalloc.so" "$@"
echo "output: $HEAPPROFILE.xxxx.heap"
