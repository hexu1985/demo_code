#!/usr/bin/env python3

import subprocess
import sys

def shell_cmd(cmd_str):
    print('shell_cmd: {}'.format(cmd_str))
    completed = subprocess.run(cmd_str, check=False, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('returncode: {}'.format(completed.returncode))
    print('Have {} bytes in stdout: {!r}'.format(
        len(completed.stdout),
        completed.stdout.decode('utf-8'))
        )
    print('Have {} bytes in stderr: {!r}'.format(
        len(completed.stderr),
        completed.stderr.decode('utf-8'))
        )
    if completed.returncode == 0:
        return (completed.returncode, completed.stdout.decode('utf-8'))
    else:
        return (completed.returncode, completed.stderr.decode('utf-8'))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {} cmd".format(sys.argv[0]))
        sys.exit(1)

    ret, msg = shell_cmd(sys.argv[1])
    print("ret: {}".format(ret))
    print("msg: {}".format(msg))
