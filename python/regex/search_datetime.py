#!/usr/bin/env python3

import re
import datetime

def search_datetime(line):
    pattern = r'\.'+'[0-9]'*8+'-'+'[0-9]'*6+r'\.'
    print("line: {}".format(line))
    results = re.search(pattern, line)
    if results is not None:
        print(results.group(0)[1:-1])
        datestr = results.group(0)[1:-1]
        dt = datetime.datetime.strptime(datestr, "%Y%m%d-%H%M%S")
        print(dt)

if __name__ == "__main__":
    search_datetime('safety_collision.log.info.20220912-094628.22874')
    search_datetime('safety.log.info.20220926-083526.9806')
    search_datetime('safety.log.info.20220926-083526ss.9806')

