#coding=utf-8
'''
Created on 2017年1月4日
@author: Administrator
'''
import time,sched
 
#周期性执行给定的任务
 
#初始化sched模块的scheduler类
#第一个参数是一个可以返回时间戳的函数，第二个参数可以在定时未到达之前阻塞。
s = sched.scheduler(time.time,time.sleep)
 
class A(object):
    def event_func1(self):
        print "func1 Time:",time.time()
         
    def perform1(self, inc):
        s.enter(inc,0,self.perform1,(inc,))
        self.event_func1()
        
    def event_func2(self):
        print "func2 time:",time.time()
        
    def perform2(self, inc):
        s.enter(inc,0,self.perform2,(inc,))
        self.event_func2()
    
def mymain(func,inc=2):
    if func == '1':
        s.enter(0,0,a.perform1,(5,))#每5秒钟执行perform1
    if func == '2':
        s.enter(0,0,a.perform2,(10,))#每10秒执行perform2
 
if __name__ == "__main__":
    a = A()
    mymain('1')
    mymain('2')
    s.run()

