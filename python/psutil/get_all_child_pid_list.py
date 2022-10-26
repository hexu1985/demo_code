import psutil
import sys

pid=1
if len(sys.argv) > 1:
    pid = int(sys.argv[1])

print("pid: {}".format(pid))

p = psutil.Process(pid)
print("child_pid: {}".format(p.children()))
print("len of child_pid: {}".format(len(p.children())))

class AllChildPidList:
    def __init__(self, pid):
        self.pid = pid
        self.child_pid_list = []

    def walk(self, pid):
        p = psutil.Process(pid)
        for child in p.children():
            self.child_pid_list.append(child.pid)
            self.walk(child.pid)

    def get(self):
        if not self.child_pid_list:
            self.walk(self.pid)

        return self.child_pid_list

all_child_pid_list = AllChildPidList(pid)
print("all child_pid: {}".format(all_child_pid_list.get()))
print("len of all child_pid: {}".format(len(all_child_pid_list.get())))

