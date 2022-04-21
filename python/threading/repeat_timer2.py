import threading
import time

class A:
    def create_timer(self):
        timer = threading.Timer(2,self.fun_timer)
        timer.start()

    def fun_timer(self):
        print('hello timer')
        #重复构造定时器
        timer = threading.Timer(5.8,self.fun_timer)
        timer.start()
        print("timer is daemon:{}".format(timer.isDaemon()))
        print("timer: {}, id: {}".format(timer, id(timer)))

a = A()
a.create_timer()

while True:
    time.sleep(1.0)
    break
