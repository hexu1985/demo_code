
import pathlib
import logging
from workflow_node import WorkflowNode
from worker_thread import WorkerThread

LOGGER = logging.getLogger()

class WorkflowNodeSet:
    def __init__(self, dir_path):
        self.set_path = dir_path
        self.worker = WorkerThread("[{}]".format(dir_path))
        self.worker.start()
        self.node_lst = []
        for node_path in self.get_nodepath_list(dir_path):
            self.node_lst.append(WorkflowNode(node_path))
        LOGGER.info('create WorkflowNodeSet("{}"), node_list:{}'.format(dir_path, self.node_lst))

    def __str__(self):
        return 'WorkflowNodeSet("{}")'.format(self.set_path)

    def __repr__(self):
        return 'WorkflowNodeSet("{}")'.format(self.set_path)

    def get_nodepath_list(self, dir_path):
        nodepath_lst = []
        p = pathlib.Path(dir_path).resolve()
        for f in p.glob("*"):
            if f.name[0] == '.':
                continue
            if f.is_dir():
                nodepath_lst.append(f)
        nodepath_lst.sort(key=lambda path: path.name)
        return nodepath_lst

    def run(self):
        class NodeTask:
            def __init__(self, node):
                self.node = node

            def execute(self):
                self.node.run()
                self.node.wait()

        for node in self.node_lst:
            self.worker.putTask(NodeTask(node))

        self.worker.stop()

    def wait(self):
        self.worker.join()


if __name__ == "__main__":
    print("test shell_command_executor.py")
    logging.basicConfig(level=logging.DEBUG)

    workflow = WorkflowNodeSet("./workflow")
    workflow.run()
    workflow.wait()
