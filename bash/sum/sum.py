#!/usr/bin/env python3

import sys
import os.path

def get_money(line):
    if line.startswith('#') or len(line.strip()) == 0:
        return None
    return float(eval(line))

if len(sys.argv) != 2:
    print("usage: {} datafile".format(sys.argv[0]))
    sys.exit(1)

money_list = []
with open(sys.argv[1], 'r', encoding='UTF-8') as f:
    for line in f.readlines():
        m = get_money(line)
        if m is not None:
            money_list.append(m)

print(sum(money_list))

