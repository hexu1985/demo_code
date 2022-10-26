import psutil
import sys

pid=1
if len(sys.argv) > 1:
    pid = int(sys.argv[1])

print("pid: {}".format(pid))

p = psutil.Process(pid)
print("child_pid: {}".format(p.children()))

