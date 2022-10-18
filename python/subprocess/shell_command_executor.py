#!/usr/bin/env python3

import os
import subprocess
import logging

LOGGER = logging.getLogger()

class ShellCommandExecutor:
    def __init__(self, cmd):
        self.cmd = cmd
        self.proc = None
        self.pipe_r, self.pipe_w = os.pipe()
        LOGGER.info("create ShellCommandExecutor(cmd=[{}])".format(self.cmd))

    def __str__(self):
        return 'ShellCommandExecutor("{}")'.format(self.cmd)

    def __repr__(self):
        return 'ShellCommandExecutor("{}")'.format(self.cmd)

    def run(self):
        try:
            self.proc = subprocess.Popen(self.cmd, shell=True, close_fds=True,
                    stdout=self.pipe_w, stderr=self.pipe_w)
            LOGGER.info('run cmd [{}]'.format(self.cmd))
            os.close(self.pipe_w)
        except subprocess.CalledProcessError as err:
            LOGGER.error('run cmd [{}] error: {}'.format(self.cmd, err))

    def wait(self):
        if not self.proc:
            LOGGER.error("cmd: [{}] is not run".format(self.cmd))
            return -1

        output = os.fdopen(self.pipe_r)
        for line in output:
            LOGGER.info("cmd: [{}] output: {}".format(self.cmd, line.rstrip()))

        ret = self.proc.wait()
        LOGGER.info("cmd: [{}] complete with ret: {}".format(self.cmd, ret))
        return ret


if __name__ == "__main__":
    print("test shell_command_executor.py")
    logging.basicConfig(level=logging.DEBUG)
    cmds = []

    cmds.append(ShellCommandExecutor("cd /tmp && pwd"))
    cmds.append(ShellCommandExecutor("./test.sh 3"))
    cmds.append(ShellCommandExecutor("./nosuchfile.sh"))

    for cmd in cmds:
        cmd.run()

    for cmd in cmds:
        cmd.wait()
