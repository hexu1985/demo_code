#!/usr/bin/env python3

import os
import subprocess
import logging
import datetime
import sys
import os
import pathlib

LOGGER = logging.getLogger()

class ShellCommandExecutor:
    def __init__(self, cmd, env=None):
        self.cmd = cmd
        self.env = env
        if not self.env:
            self.env = os.environ.copy()
        self.proc = None
        self.logfile = None
        log_dir = self.get_current_file_path()
        self.logfile_path = log_dir+"/log/shell_command_executor.log.%s"%datetime.datetime.now().strftime('%Y%m%d-%H%M%S.%f')
        LOGGER.info("create ShellCommandExecutor(cmd=[{}])".format(self.cmd))

    def get_current_file_path(self):
        current_file_path=os.path.dirname(sys.argv[0])
        if not current_file_path:
            current_file_path = os.getcwd()
        current_file_path = pathlib.Path(current_file_path).resolve()
        return str(current_file_path)

    def __str__(self):
        return 'ShellCommandExecutor("{}")'.format(self.cmd)

    def __repr__(self):
        return 'ShellCommandExecutor("{}")'.format(self.cmd)

    def run(self):
        try:
            self.logfile = open(self.logfile_path, 'w')
            self.proc = subprocess.Popen(self.cmd, shell=True, env=self.env, close_fds=True,
                    stdout=self.logfile, stderr=self.logfile)
            LOGGER.info('run cmd [{}], logfile_path: {}'.format(self.cmd, self.logfile_path))
        except Exception as err:
            LOGGER.error('run cmd [{}] error: {}'.format(self.cmd, err))

    def wait(self):
        if not self.proc:
            LOGGER.error("cmd: [{}] is not run".format(self.cmd))
            return -1

        ret = self.proc.wait()
        print("*"*20, file=self.logfile)
        print("cmd [{}]".format(self.cmd), file=self.logfile)
        self.logfile.close()
        LOGGER.info("cmd: [{}] complete with ret: {}, logfile_path: {}".format(self.cmd, ret, self.logfile_path))


if __name__ == "__main__":
    print("test shell_command_executor.py")
    logging.basicConfig(level=logging.DEBUG)
    cmds = []

    cmds.append(ShellCommandExecutor("cd /tmp && pwd"))
    cmds.append(ShellCommandExecutor('echo "DISK_PATH=$DISK_PATH"'))
    cmds.append(ShellCommandExecutor('echo "DISK_PATH=$DISK_PATH" 1>&2'))
    cmds.append(ShellCommandExecutor('./nosuchfile.sh'))

    for cmd in cmds:
        cmd.run()

    for cmd in cmds:
        cmd.wait()
