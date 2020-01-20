#!/usr/bin/env bash

mp3_dir=mp3_files
wav_dir=wav_files

for mp3_file in $(ls -1 ${mp3_dir}/*.mp3)
do
#    echo ${mp3_file}
    base_file_name=${mp3_file%.mp3}
    base_file_name=${base_file_name##*/}
    ./mp3towav.py ${mp3_file} "${wav_dir}/${base_file_name}.wav"
#    echo ${base_file_name}
done

