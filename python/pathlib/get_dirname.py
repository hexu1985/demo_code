import pathlib
import logging
import os
import sys

LOGGER = logging.getLogger()

def get_dirname(path):
    p = pathlib.Path(path)
    return p.parent.resolve()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    path = __file__
    if len(sys.argv) > 1:
        path = sys.argv[1]
    print("dirname {} is {}".format(path, get_dirname(path)))
