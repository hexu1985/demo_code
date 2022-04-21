import threading
import time
from functools import partial

class A:
    def create_timer(self):
        timer = threading.Timer(2, partial(self.fun_timer, "123"))
        timer.start()

    def fun_timer(self, msg):
        print('hello timer, msg: {}'.format(msg))
        #重复构造定时器
        timer = threading.Timer(5.8, partial(self.fun_timer, "abc"))
        timer.start()
        print("timer is daemon:{}".format(timer.isDaemon()))
        print("timer: {}, id: {}".format(timer, id(timer)))

a = A()
a.create_timer()

while True:
    time.sleep(1.0)
    break
