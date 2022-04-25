
import os
import sys
import pathlib
import logging
import time
import signal
import argparse
import threading
import schedule # need pip3 install schedule

from logging_config import init_logging_config
from uevent_publisher import UeventPublisher
from workflow_service import WorkflowService

LOGGER = logging.getLogger()

def get_current_file_path():
    current_file_path=os.path.dirname(sys.argv[0])
    if not current_file_path:
        current_file_path = os.getcwd()
    current_file_path = pathlib.Path(current_file_path).resolve()
    return str(current_file_path)

def receive_signal(signum, stack):
    LOGGER.info('Received:{}'.format(signum))
    if signum == signal.SIGUSR1:
        workflow_service = WorkflowService()
        workflow_service.OnSignalReceived(signum, stack)

def send_self_signal_sigusr1():
    os.kill(os.getpid(), signal.SIGUSR1)

def mkdir_if_not_exists(dir_path):
    path = pathlib.Path(dir_path)
    if path.exists():
        if not path.is_dir():
            LOGGER.error('path "{}" already exist but not dir'.format(path))
            return False
        elif not os.access(dir_path, os.W_OK):
            LOGGER.error('path "{}" already exist but not write permission'.format(path))
            return False
        else:
            return True
    else:
        path.mkdir()
        return True


class ArgManager:
    def __init__(self):
        self.parser = argparse.ArgumentParser(
            description="workflow service")

        self.parser.add_argument('--work_dir', default="", action="store",
                                 dest="WORK_DIR", type=str,
                                 help='work_dir path'
                                 'example: --work_dir /tmp/workflow')
        self._args = None

    def args(self):
        """Get parsed args."""
        if self._args is None:
            self._args = self.parser.parse_args()
        return self._args

class SchedThread(threading.Thread):
    def __init__(self):
        super().__init__()
        schedule.every().day.at("21:00").do(send_self_signal_sigusr1)

    def run(self):
        while True:
            schedule.run_pending()
            time.sleep(1.0)

def main():
    # parse arguments
    arg_manager = ArgManager()
    args = arg_manager.args()

    # set work_dir, and create work_dir if need
    work_dir = get_current_file_path()
    if args.WORK_DIR:
        work_dir = args.WORK_DIR
    if not mkdir_if_not_exists(work_dir):
        LOGGER.error("work_dir: {} is not available".format(work_dir))
        sys.exit(-1)

    ### init log config
    log_dir = work_dir+"/log"
    if not mkdir_if_not_exists(log_dir):
        LOGGER.error("log_dir: {} is not available".format(log_dir))
        sys.exit(-1)
    init_logging_config(log_dir, "workflow.service", logging.INFO)

    LOGGER.info("args: {}".format(args))

    ### create UeventPublisher
    uevent_publisher = UeventPublisher(work_dir)

    ### create WorkflowService
    workflow_service = WorkflowService()
    workflow_service.start(work_dir)

    ### register observer
    signal.signal(signal.SIGUSR1, receive_signal)
    uevent_publisher.addObserver(workflow_service)

    ### start UeventPublisher
    uevent_publisher.setDaemon(True)
    uevent_publisher.start()

    ### start crontab task
    sched_thread = SchedThread()
    sched_thread.setDaemon(True)
    sched_thread.start()

    while True:
        time.sleep(1.0)

if __name__ == "__main__":
    main()
