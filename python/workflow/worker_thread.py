import threading
import logging
import queue
import time

LOGGER = logging.getLogger()

class StopWorkerThreadException(Exception):
    def __init__(self):
        pass

    def __repr__(self):
        return "StopWorkerThreadException"

    def __str__(self):
        return "StopWorkerThreadException"

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
            except StopWorkerThreadException as e:
                LOGGER.info("get stoptask and exit workthread")
                break
            except:
                LOGGER.error("task execute unknown error: {}".format(sys.exc_info()[0]))

    def putTask(self, task):
        self.task_queue.put(task)

    def stop(self):
        class StopTask:
            def __init__(self):
                LOGGER.info("create StopTask")

            def execute(self):
                raise StopWorkerThreadException
    
        self.putTask(StopTask())

if __name__ == "__main__":
    class DemoTask:
        def __init__(self, name):
            self.name = name

        def execute(self):
            print("execute {}".format(self.name))
            time.sleep(1.0)

    print("test of worker_thread.py")
    worker = WorkerThread()
    worker.start()

    print("start task")
    for i in range(1, 5):
        worker.putTask(DemoTask(i))

    print("stop worker thread")
    worker.stop()

    print("join worker thread")
    worker.join()
    print("exit of worker_thread.py")







        
