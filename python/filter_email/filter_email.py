#!/usr/bin/env python3

import sys
import re

def filter_email_from_file(filepath):
    email_list = []
    pattern = r'(\w+\.)*\w+@(\w+\.)+[A-Za-z]+'
    regexes = re.compile(pattern)
    with open(filepath, 'r', encoding='UTF-8') as f:
        for line in f.readlines():
            match = regexes.search(line)
            if match:
                s = match.start()
                e = match.end()
                substr = line[s:e]
                print(substr)


if __name__ == '__main__':
    filter_email_from_file(sys.argv[1])
