#!/usr/bin/env python3

import psutil
import sys

def get_disk_usage_rate(path):
    du = psutil.disk_usage(path)
    return du.percent

if __name__ == "__main__":
    for p in sys.argv[1:]:
        du = get_disk_usage_rate(p)
        print("disk {}, used {}%".format(p, du))
