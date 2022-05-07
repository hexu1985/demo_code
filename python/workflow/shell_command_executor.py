#!/usr/bin/env python3

import os
import subprocess
import logging
import datetime
import sys
import os
import pathlib
import time

LOGGER = logging.getLogger()

class ShellCommandExecutor:
    def __init__(self, cmd, timeout=7200):
        self.cmd = cmd
        self.proc = None
        self.logfile = None
        self.timeout = timeout
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
            self.proc = subprocess.Popen(self.cmd, close_fds=True, stdout=self.logfile, stderr=self.logfile)
            self.start_time = time.time()
            LOGGER.info('run cmd [{}], logfile_path: {}'.format(self.cmd, self.logfile_path))
        except Exception as err:
            LOGGER.error('run cmd [{}] error: {}'.format(self.cmd, err))
            if self.logfile:
                self.logfile.close()
            self.proc = None

    def wait(self):
        if not self.proc:
            LOGGER.error("cmd: [{}] error not run".format(self.cmd))
            return -1

        try:
            now = time.time()
            time_to_wait = self.timeout - (now - self.start_time)
            ret = self.proc.wait(time_to_wait)
            now = time.time()
            print("*"*20, file=self.logfile)
            print("cmd [{}]".format(self.cmd), file=self.logfile)
            LOGGER.info("cmd: [{}] complete with ret: {}, logfile_path: {}, escaped time: {}s".format(self.cmd, ret, self.logfile_path, int(now-self.start_time)))
        except subprocess.TimeoutExpired as err:
            self.proc.kill()
            print("*"*20, file=self.logfile)
            print("cmd [{}] timeout".format(self.cmd), file=self.logfile)
            LOGGER.info("cmd: [{}] was killed because timeout, logfile_path: {}".format(self.cmd, self.logfile_path))

        self.logfile.close()


if __name__ == "__main__":
    print("test shell_command_executor.py")
    logging.basicConfig(level=logging.DEBUG)
    cmds = []

    cmds.append(ShellCommandExecutor('./workflow/step01/backup/step01_test01.sh', 3))
    cmds.append(ShellCommandExecutor('./workflow/step01/backup/step01_test02.sh', 3))
    cmds.append(ShellCommandExecutor('./nosuchfile.sh'))

    for cmd in cmds:
        cmd.run()

    for cmd in cmds:
        cmd.wait()
