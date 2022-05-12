from worker_thread2 import WorkerThread
import time
import functools
import logging

def test_func():
    raise TypeError("abcde")

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    class DemoTask:
        def __init__(self, name):
            self.name = name

        def print_int(self, i):
            print("execute {} - {}".format(self.name, i))
            time.sleep(1.0)

    print("test of worker_thread.py")
    worker = WorkerThread()
    worker.start()

    task = DemoTask("demo task") 
    print("start task")
    for i in range(1, 5):
        worker.putTask(functools.partial(task.print_int, i))

    worker.putTask(test_func)

    for i in range(6, 10):
        worker.putTask(functools.partial(task.print_int, i))

    print("stop worker thread")
    worker.stop()

    print("join worker thread")
    worker.join()
    print("exit of worker_thread.py")
