import threading
import logging
import queue
import time

LOGGER = logging.getLogger()

#class StopWorkerThread:
#    def execute(self):
#        throw 

class WorkerThread(threading.Thread):
    def __init__(self, name=""):
        super().__init__()
        self.task_queue = queue.Queue()
        self.name = name

    def fetch_and_exectue_task_once(self):
        task = self.task_queue.get()
        try:
            task.execute()
        except AttributeError as e:
            LOGGER.error("task attribute error: {}".format(e))

    def run(self):
        LOGGER.info("worker {} is running".format(self.name))
        while True:
            try:
                self.fetch_and_exectue_task_once()
            except:
                LOGGER.error("task execute unknown error: {}".format(sys.exc_info()[0]))

    def putTask(self, task):
        self.task_queue.put(task)

if __name__ == "__main__":
    class DemoTask:
        def __init__(self, name):
            self.name = name

        def execute(self):
            print("execute {}".format(self.name))
            time.sleep(0.5)

    print("test of worker_thread.py")
    worker = WorkerThread()
    worker.setDaemon(True)
    worker.start()

    for i in range(1, 5):
        worker.putTask(DemoTask(i))

    #worker.stop()
    while True:
        time.sleep(1)







        
