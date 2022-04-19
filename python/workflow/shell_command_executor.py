#!/usr/bin/env python3

import os
import subprocess
import logging

LOGGER = logging.getLogger()

class ShellCommandExecutor:
    def __init__(self, cmd, env=None):
        self.cmd = cmd
        self.env = env
        if not self.env:
            self.env = os.environ.copy()
        self.proc = None
        LOGGER.info("create ShellCommandExecutor(cmd=[{}])".format(self.cmd))

    def __str__(self):
        return 'ShellCommandExecutor("{}")'.format(self.cmd)

    def __repr__(self):
        return 'ShellCommandExecutor("{}")'.format(self.cmd)

    def run(self):
        try:
            self.proc = subprocess.Popen(self.cmd, shell=True, env=self.env, close_fds=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            LOGGER.info('run cmd [{}]'.format(self.cmd))
        except subprocess.CalledProcessError as err:
            LOGGER.error('run cmd [{}] error: {}'.format(self.cmd, err))

    def wait(self):
        if not self.proc:
            LOGGER.error("cmd: [{}] is not run".format(self.cmd))
            return -1

        ret = self.proc.wait()
        stdout = self.proc.stdout.read().decode('utf-8') if self.proc.stdout else ""
        stderr = self.proc.stderr.read().decode('utf-8') if self.proc.stderr else ""
        LOGGER.info("cmd: [{}] complete with ret: {}\n\tstdout:[{}]\n\tstderr:[{}]".format(self.cmd, ret, stdout, stderr))


if __name__ == "__main__":
    print("test shell_command_executor.py")
    logging.basicConfig(level=logging.DEBUG)
    cmds = []

    cmds.append(ShellCommandExecutor("cd /tmp && pwd"))
    cmds.append(ShellCommandExecutor('echo "DISK_PATH=$DISK_PATH"', env = {"DISK_PATH":"abc"}))
    cmds.append(ShellCommandExecutor('echo "DISK_PATH=$DISK_PATH" 1>&2', env = {"DISK_PATH":"abc"}))
    cmds.append(ShellCommandExecutor('./nosuchfile.sh', env = {"DISK_PATH":"abc"}))

    for cmd in cmds:
        cmd.run()

    for cmd in cmds:
        cmd.wait()
