#!/usr/bin/env python3

import pathlib
import sys

def print_path_types(path):
    f = pathlib.Path(path)
    hfmt = '{:18s}' + ('  {:>5}' * 6)
    print(hfmt.format('Name', 'File', 'Dir', 'Link', 'FIFO', 'Block', 'Character'))
    print()

    fmt = '{:20s}  ' + ('{!r:>5}  ' * 6)
    print(fmt.format(
        str(f),
        f.is_file(),
        f.is_dir(),
        f.is_symlink(),
        f.is_fifo(),
        f.is_block_device(),
        f.is_char_device(),
    ))

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("usage: {} <file_path>".format(sys.argv[0]))
        sys.exit(1)

    print_path_types(sys.argv[1])

