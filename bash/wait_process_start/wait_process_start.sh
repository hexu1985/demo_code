#!/bin/bash

debug=1

CURRENT_FILE_NAME=$(basename $0)
PROCESS_CMD_PATTERN=
WAITING_TIMEOUT_SEC=3

print_usage() {
    echo 'usage: wait_process_start.sh -p process_cmd_pattern [-t timeout_sec]'
}

# count_process include exclude
count_process() {
    local include_pattern=$(echo $1 | sed -e 's/[a-zA-Z]/[&]/')
    local exclude_pattern=$2
    ps aux | grep "${include_pattern}" | grep -v "${exclude_pattern}" | wc -l
}

while getopts p:t: opt; do
    case $opt in
        p  ) PROCESS_CMD_PATTERN="${OPTARG}" ;;
        t  ) WAITING_TIMEOUT_SEC="${OPTARG}" ;;
        \? ) print_usage
             exit 1
    esac
done

if [ -z "$PROCESS_CMD_PATTERN" ]
then
    print_usage
    exit 1
fi

for i in $(seq ${WAITING_TIMEOUT_SEC})
do
    count=`count_process "${PROCESS_CMD_PATTERN}" "${CURRENT_FILE_NAME}"`
    ((debug)) && echo "count: ${count}"
    if (( count >= 1 ))
    then
        echo "found ${PROCESS_CMD_PATTERN}, count ${count}"
        exit 0
    fi
    sleep 1
done

echo "not found ${PROCESS_CMD_PATTERN}"
exit 1
