#!/usr/bin/env python3

import pathlib
import sys
import traceback  

def get_file_size(path):
    try:
        f = pathlib.Path(path)

        if not f.is_file():
            print("{} is not file".format(f))
            return 0

        if f.is_symlink():
            print("{} is link".format(f))
            return 0

        stat_info = f.stat()
        return stat_info.st_size

    except:
        traceback.print_exc(limit=1, file=sys.stdout)
        return 0

def dir_disk_usage_statistics(dir_path):
    p = pathlib.Path(dir_path)
    totol_size = 0
    for f in p.rglob('*'):
        print("get_file_size({})".format(f))
        totol_size += get_file_size(f)

    return totol_size

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("usage: {} <dir_path>".format(sys.argv[0]))
        sys.exit(1)

    print("{} size: {}".format(sys.argv[1], dir_disk_usage_statistics(sys.argv[1])))


