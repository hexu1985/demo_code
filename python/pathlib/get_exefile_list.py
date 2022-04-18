#!/usr/bin/env python3

import pathlib
import os
import sys


def get_exefile_list(dir_path):
    exefile_lst = []
    p = pathlib.Path(dir_path).resolve()
    for f in p.glob("*"):
        if os.access(f, os.X_OK):
            exefile_lst.append(f)
    return exefile_lst

if __name__ == "__main__":
    dir_path = "."
    if len(sys.argv) > 1:
        dir_path = sys.argv[1]

    print("dir_path: {}".format(dir_path))
    cmd_lst = get_exefile_list(dir_path)
    print("cmd_lst: {}".format(cmd_lst))
    for cmd in cmd_lst:
        print("cmd {}".format(cmd))
