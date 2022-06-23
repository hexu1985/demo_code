#!/usr/bin/env bash

function parser_rsync_log_file()
{
    local input_file=$1
    local output_file=$2
    cat ${input_file} | \
        grep -v '^sending incremental file list' | \
        grep -v '^sent.*received' | \
        grep -v '^total size is' | \
        grep -v '^\./$' | grep -v '^$' > ${output_file}
    local count=`wc -l ${output_file} | awk '{print $1}'`
    return ${count}
}

result_file=`mktemp -t rsync.result.$$.XXXXXXXX`
echo "parser_rsync_log_file rsync1.log ${result_file}"
parser_rsync_log_file rsync1.log ${result_file}
echo $?

echo "parser_rsync_log_file rsync2.log ${result_file}"
parser_rsync_log_file rsync2.log ${result_file}
echo $?

rm ${result_file}
