#!/usr/bin/env bash

CURRENT_FILE_PATH=$(cd `dirname $0` && pwd)
echo "CURRENT_FILE_PATH=${CURRENT_FILE_PATH}, by \$0"

CURRENT_FILE_PATH=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)
echo "CURRENT_FILE_PATH=${CURRENT_FILE_PATH}, by \${BASH_SOURCE[0]}"
