
import sys
import re

if len(sys.argv) != 2:
    print("usage: {} icmp_log_file".format(sys.argv[0]))
    sys.exit(1)

def get_time(line):
    m = re.match('.*time=(\d+(\.\d+)?) ms', line)
    if m is not None:
        return m.group(1)
    else:
        return None;

time_lists=[]
filename=sys.argv[1]
with open(filename) as f:
    for line in f:
        time = get_time(line)
        if time is not None: 
            time_lists.append(float(time))

time_lists.sort()
time_lists = time_lists[3:-3]
s = sum(time_lists)
avg = s / len(time_lists)
print(avg)
