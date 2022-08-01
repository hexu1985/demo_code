#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2010 Doug Hellmann.  All rights reserved.
#
"""Show the built-in argument actions.
"""

#end_pymotw_header
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-f', action='append',
                    dest='file_list',
                    default=[],
                    help='file list')

parser.add_argument('--version', action='version',
                    version='%(prog)s 1.0')

results = parser.parse_args()
print('file_list       = {!r}'.format(results.file_list))

# example -f "a.txt" -f "b.txt"
