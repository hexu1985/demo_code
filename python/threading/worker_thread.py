import threading
import logging

LOGGER = logging.getLogger()

class WorkerThread(threading.Thread):
    def __init__(self):
        super().__init__()
        self.task_queue = queue.Queue()

    def fetch_and_exectue_task_once(self):
        task = self.task_queue.get()
        try:
            task.execute()
        except AttributeError as e:
            LOGGER.error("task attribute error: {}".format(e))

    def run(self):
        while True:
            try:
                self.fetch_and_exectue_task_once()
            except:
                LOGGER.error("task execute unknown error: {}".format(sys.exc_info()[0]))

    def putTask(self, task):
        self.task_queue.put(task)



if __name__ == "__main__":
    print("test of worker_thread.py")






        
