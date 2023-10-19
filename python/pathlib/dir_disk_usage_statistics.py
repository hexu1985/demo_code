#!/usr/bin/env python3

import pathlib
import sys
import traceback  

def get_file_size(path):
    try:
        f = pathlib.Path(path)

        stat_info = f.lstat()
        return stat_info.st_size

    except:
        traceback.print_exc(limit=1, file=sys.stdout)
        return 0

def dir_disk_usage_statistics(dir_path):
    p = pathlib.Path(dir_path)
    total_size = get_file_size(dir_path)
    for f in p.rglob('*'):
        print("get_file_size({})".format(f))
        total_size += get_file_size(f)
    return total_size

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("usage: {} <dir_path>".format(sys.argv[0]))
        sys.exit(1)

    print("{} size: {}".format(sys.argv[1], dir_disk_usage_statistics(sys.argv[1])))


