#!/usr/bin/env bash

debug=1

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

for file_name in "${file_name_list[@]}"
do
    (( debug == 1 )) && echo "process ${file_name}"
    replace_in_file "$1" "&_" "${file_name}"
done
