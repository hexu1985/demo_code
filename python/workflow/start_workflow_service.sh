#!/bin/bash

CURRENT_FILE_DIRECTORY=$(cd `dirname $0` && pwd)

echo $CURRENT_FILE_DIRECTORY
workflow_serive_file=${CURRENT_FILE_DIRECTORY}/main.py
#current_date=$(date +%Y%m%d_%H%M%S)
nohup python3 ${workflow_serive_file} >& /dev/null &
