#!/usr/bin/env python3

import psutil

def get_mount_points():
    partitions = psutil.disk_partitions()
    return [ p.mountpoint for p in partitions ]

if __name__ == "__main__":
    mount_points = get_mount_points()
    print(mount_points)
