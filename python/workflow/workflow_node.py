
import os
import pathlib
import logging
from shell_command_executor import ShellCommandExecutor

LOGGER = logging.getLogger()

class WorkflowNode:
    def __init__(self, dir_path):
        self.node_path = dir_path
        self.cmd_lst = []
        for exefile_path in self.get_exefile_list(dir_path):
            cmd_str="{}".format(exefile_path)
            self.cmd_lst.append(ShellCommandExecutor(cmd_str))
        LOGGER.info('create WorkflowNode("{}"), cmd_list:{}'.format(dir_path, self.cmd_lst))

    def __str__(self):
        return 'WorkflowNode("{}")'.format(self.node_path)

    def __repr__(self):
        return 'WorkflowNode("{}")'.format(self.node_path)

    def get_exefile_list(self, dir_path):
        exefile_lst = []
        p = pathlib.Path(dir_path).resolve()
        for f in p.glob("*"):
            if f.name[0] == '.':
                continue
            if not f.is_file():
                continue
            if os.access(f, os.X_OK):
                exefile_lst.append(f)
        exefile_lst.sort(key=lambda path: path.name)
        return exefile_lst

    def run(self):
        for cmd in self.cmd_lst:
            cmd.run()

    def wait(self):
        for cmd in self.cmd_lst:
            cmd.wait()


if __name__ == "__main__":
    print("test shell_command_executor.py")
    logging.basicConfig(level=logging.DEBUG)
    cmds = []

    cmds.append(WorkflowNode("./workflow/step01"))
    cmds.append(WorkflowNode("./workflow/step02"))

    for cmd in cmds:
        cmd.run()
        cmd.wait()
