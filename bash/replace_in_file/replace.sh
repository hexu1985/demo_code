#!/usr/bin/env bash

function replace_in_file {
    local be_replaced=$1
    local replace_with=$2
    local file_name=$3
    local cmd="sed -i 's/\<${be_replaced}\>/${replace_with}/g' ${file_name}"
    (( debug == 1 )) && echo $cmd
    eval $cmd
}

replace_in_file "up_caffe_model" "&_" $1

