#!/usr/bin/env python3

import sys
import re

def check_enum_start(line, enum_name):
    tmp_str = line.strip()
    if (tmp_str.startswith("enum") and tmp_str.find(enum_name) != -1):
#        print(tmp_str)
        return True
    return False

def check_enum_end(line):
    tmp_str = line.strip()
    if (tmp_str.find("};") != -1):
#        print(tmp_str)
        return True
    return False

def filter_enum_entry(enum_list, line):
    r'\w *= *(.*),'
    m = re.match(r'\s*(\w+)\s*=.*', line)
    if not m: 
        return
    enum_list.append(m.group(1))

def read_enum_list_from_file(filepath, enum_name):
    enum_start = False
    enum_end = False
    
    enum_list = []
    with open(filepath, 'r') as f:
        for line in f.readlines():
            if enum_end:
                break
    
            if not enum_start:
                if check_enum_start(line, enum_name):
                    enum_start = True
                continue
    
            if check_enum_end(line):
                enum_end = True
                continue
    
            filter_enum_entry(enum_list, line)

    return enum_list

def gen_perror(enum_list):
    for enum_entry in enum_list:
        print('case %s: return "%s";' % (enum_entry, enum_entry))

if __name__ == '__main__':
    enum_list = read_enum_list_from_file(sys.argv[1], sys.argv[2])
#    print(enum_list)
    gen_perror(enum_list)
