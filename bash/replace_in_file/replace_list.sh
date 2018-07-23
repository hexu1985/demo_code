#!/usr/bin/env bash

function replace_in_file {
    local be_replaced=$1
    local replace_with=$2
    local file_name=$3
    local cmd="sed -i 's/\<${be_replaced}\>/${replace_with}/g' ${file_name}"
    (( debug == 1 )) && echo $cmd
    eval $cmd
}

file_name_list=(
    "include/stsdk/AlignerBodyContour.hpp"
    "include/stsdk/AlignerBody.hpp"
    "include/stsdk/AlignerHeadShoulder.hpp"
    "include/stsdk/AlignerUpperBody.hpp"
    "src/stsdk/AlignerBodyContour.cpp"
    "src/stsdk/AlignerBody.cpp"
    "src/stsdk/AlignerHeadShoulder.cpp"
    "src/stsdk/AlignerUpperBody.cpp"
    )

be_replaced_list=(
    "up_caffe_model"
    "stability_score"
    )

for file_name in "${file_name_list[@]}"
do
    (( debug == 1 )) && echo "process ${file_name}"
    for be_replaced in "${be_replaced_list[@]}"
    do
        (( debug == 1 )) && echo "process ${be_replaced}"
    done
done

#replace_in_file "up_caffe_model" "&_" $1

