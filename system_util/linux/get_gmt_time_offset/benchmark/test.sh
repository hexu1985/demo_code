#!/usr/bin/env bash

echo "TZ=GMT ./get_gmt_time_offset"
TZ=GMT ./get_gmt_time_offset

echo "TZ=EST ./get_gmt_time_offset"
TZ=EST ./get_gmt_time_offset

echo "TZ=CET ./get_gmt_time_offset"
TZ=CET ./get_gmt_time_offset

echo "TZ='America/New_York' ./get_gmt_time_offset"
TZ='America/New_York' ./get_gmt_time_offset

echo "TZ='America/Shanghai' ./get_gmt_time_offset"
TZ='Asia/Shanghai' ./get_gmt_time_offset
