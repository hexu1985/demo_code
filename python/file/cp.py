#!/usr/bin/env python3

import sys

if len(sys.argv) != 3:
    print("usage: {} src_file dst_file".format(sys.argv[0]))
    sys.exit(1)

input_file_path = sys.argv[1]
output_file_path = sys.argv[2]
with open(input_file_path, 'r') as in_file, open(output_file_path, 'w') as out_file:
    for line in in_file:
        out_file.write(line)

