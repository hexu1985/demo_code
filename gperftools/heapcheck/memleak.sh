#!/usr/bin/env bash

#set -x

function usage {
    echo "usage: $0 program heap_file"
    exit 1
}

EXE_FILE_NAME=$1
PROFILE_FILE_NAME=$2

if [ $# != 2 ]; then
    usage
fi

if [ ! -f $EXE_FILE_NAME ]; then
    echo "$EXE_FILE_NAME not found, exit"
    usage
fi

if [ ! -f $PROFILE_FILE_NAME ]; then
    echo "$PROFILE_FILE_NAME not found, exit"
    usage
fi

pprof $EXE_FILE_NAME $PROFILE_FILE_NAME --inuse_objects --lines --heapcheck --edgefraction=1e-10 --nodefraction=1e-10 --pdf > $PROFILE_FILE_NAME.prof.pdf
echo "output: $PROFILE_FILE_NAME.prof.pdf"
