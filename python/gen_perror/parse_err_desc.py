#!/usr/bin/env python3

import sys
import re

def is_number(s):
    try:
        int(s)
        return True
    except ValueError:
        pass

    return False

def is_empty_line(s):
    return len(s.strip()) == 0

def read_enum_list_from_file(filepath, enum_name):
    enum_start = False
    
    with open(filepath, 'r', encoding='UTF-8') as f:
        for line in f.readlines():
            if is_number(line):
                enum_start = False
                continue

            if line.startswith(' ' + enum_name):
                print('case '+line.strip()+':')
                print('    return');
                enum_start = True
                continue

            if enum_start == True:
                if is_empty_line(line):
                    print('        ;')
                    enum_start = False
                    continue
                print('        '+'"'+line.strip()+'"')

if __name__ == '__main__':
    enum_list = read_enum_list_from_file(sys.argv[1], sys.argv[2])
