#!/usr/bin/env bash

echo "./get_gmt_time_offset GMT"
./get_gmt_time_offset GMT

echo "./get_gmt_time_offset EST"
./get_gmt_time_offset EST

echo "./get_gmt_time_offset CET"
./get_gmt_time_offset CET

echo "./get_gmt_time_offset 'America/New_York'" 
./get_gmt_time_offset 'America/New_York' 

echo "./get_gmt_time_offset 'Asia/Shanghai'" 
./get_gmt_time_offset 'Asia/Shanghai'
