#!/usr/bin/env python3

import re

def findall_datetime(line):
    pattern = '\\.'+'[0-9]'*8+'-'+'[0-9]'*6+'\\.'
    print("line: {}".format(line))
    for results in re.findall(pattern, line):
        print(results[1:-1])

if __name__ == "__main__":
    findall_datetime('safety_collision.log.info.20220912-094628.22874')
    findall_datetime('safety.log.info.20220926-083526.9806')

