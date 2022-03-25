#!/usr/bin/env python3

import sys
import pathlib

def list_dir_files(dir_path, file_pattern="*"):
    p = pathlib.Path(dir_path)
    return [f for f in p.glob(file_pattern) if f.is_file()]

def list_subdir_files(dir_path, subdir_pattern="*", file_pattern="*"):
    file_list = []
    p = pathlib.Path(dir_path).resolve()
    subdir_list = [f for f in p.glob(subdir_pattern) if f.is_dir()]
    for subdir in subdir_list:
        file_list.extend(list_dir_files(subdir, file_pattern))

    return file_list


if __name__ == "__main__":
    args_num = len(sys.argv)
    if args_num == 1:
        print(list_subdir_files("."))
    elif args_num == 2:
        print(list_subdir_files(sys.argv[1]))
    elif args_num == 3:
        print(list_subdir_files(sys.argv[1], sys.argv[2]))
    else:
        print(list_subdir_files(sys.argv[1], sys.argv[2], sys.argv[3]))
