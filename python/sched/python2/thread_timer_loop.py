#coding=utf-8

import time,sched
import threading
 
class LoopThread(threading.Thread):
    def __init__(self):
        super(LoopThread, self).__init__()
        self.sched = sched.scheduler(time.time,time.sleep)

    def event_func1(self):
        print "func1 Time:",time.time()
         
    def perform1(self, inc):
        self.sched.enter(inc,0,self.perform1,(inc,))
        self.event_func1()
        
    def event_func2(self):
        print "func2 time:",time.time()
        
    def perform2(self, inc):
        self.sched.enter(inc,0,self.perform2,(inc,))
        self.event_func2()
    
    def run(self):
        print('run')
        self.mymain('1')
        self.mymain('2')
        self.sched.run()

    def mymain(self, func,inc=2):
        if func == '1':
            self.sched.enter(0,0,self.perform1,(5,))#每5秒钟执行perform1
        if func == '2':
            self.sched.enter(0,0,self.perform2,(10,))#每10秒执行perform2
 
if __name__ == "__main__":
    loop_thread = LoopThread()
    loop_thread.start()
    loop_thread.join()
