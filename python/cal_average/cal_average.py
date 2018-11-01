#!/usr/bin/env python3

import sys
import re

def get_time(line):
    m = re.match('Hand2dAligner::Alignment use time: (\d+(\.\d+)?) us', line)
    if m is not None:
        return m.group(1)
    else:
        return None;

if len(sys.argv) != 2:
    print("usage: %s file" % sys.argv[0])
    sys.exit(1)

time_list = []
with open(sys.argv[1], 'r') as f:
    for line in f.readlines():
        t = get_time(line)
        if t is not None:
            time_list.append(float(get_time(line)))

total_time = sum(time_list)
average_time = total_time / len(time_list)
print(average_time)
