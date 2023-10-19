#!/usr/bin/env python3

import sys
import pathlib
import pdb

def list_file_by_mtime_from_last(dir_path, pattern="*"):
    p = pathlib.Path(dir_path)
    lst = [f for f in p.glob(pattern) if f.is_file() and not f.is_symlink()]
    def get_file_mtime(f):
        try:
            stat_info = f.lstat()
            return stat_info.st_mtime
        except:
            traceback.print_exc(limit=1, file=sys.stdout)
            return 0

    lst.sort(key=get_file_mtime, reverse=True)
    return lst

def test_list_dir(dir_path, pattern='*'):
    for p in list_file_by_mtime_from_last(dir_path, pattern):
        print(str(p))

if __name__ == "__main__":
    args_num = len(sys.argv)
    if args_num == 1:
        test_list_dir(".")
    elif args_num == 2:
        test_list_dir(sys.argv[1])
    elif args_num == 3:
        test_list_dir(sys.argv[1], sys.argv[2])

