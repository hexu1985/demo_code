#!/bin/bash
# Copyright (c) 2020 White Rhino Inc. All Rights Reserved.
# brief:
# author:   Hongda Zhang (zhanghongda@white-rhino.auto)
# date:     2020/02/04
# version:  1.0.0

f_log=${1:-/apollo/data/log/safety.INFO}
f_csv=${2:-./latc.csv}
f_png=${3:-./latc.png}

cwd=$(cd `dirname $BASH_SOURCE[0]`; pwd)

# check input dat file
[ -f $f_log ] || {
    echo "error: $f_log doesn't exits!"
    exit 0
}

echo "time, perception, prediction, planning, drvmod(9A 8R 7S 6Y 5M 4E)" > "$f_csv"
gawk -F'\\(|\\)| +' '
function get_mode_num2(mod_str) {
    switch (mod_str) {
        case "COMPLETE_AUTO_DRIVE": return 900
        case "AUTO_STEER_ONLY": return 870
        case "AUTO_SPEED_ONLY": return 850
        case "REMOTE_ENGAGE": return 800
        case "SAFETY_MODE": return 700
        case "READY": return 600
        case "COMPLETE_MANUAL": return 500
        case "EMERGENCY_MODE ": return 400
        default: return -1
    }
}
function get_mode_num(num) {
    switch (num) {
        case 0: return 600
        case 1: return 900
        case 2: return 870
        case 3: return 850
        case 4: return 500
        case 5: return 800
        case 6: return 700
        case 7: return 400
        default: return -1
    }
}
/LOCATIONCHECK/ {
    drvmod = get_mode_num($22)
}
/latency-lidar/ {
    t = $11
    percep = $14
    predict = $17
    planning = $20
    if (!t) t = 0
    if (!percep) percep = 0
    if (!predict) predict = 0
    if (!planning) planning = 0
    if (!drvmod) drvmod = -1
    print t", "percep", "predict", "planning", "drvmod
}' "$f_log" >> "$f_csv"

line_count=$(wc -l $f_csv | awk '{ print $1 }')
echo "line_count: $line_count"
if (( line_count <= 1 ))
then
    echo "no data in $f_csv"
    exit 1
fi

shift
python3 $cwd/lib/plotxy.py "$f_csv" 0 -1 "$f_png"
