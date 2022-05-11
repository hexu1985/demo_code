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
 
#被周期性调度触发的函数
def event_func1():
    print "func1 Time:",time.time()
     
def perform1(inc):
    s.enter(inc,0,perform1,(inc,))
    event_func1()
    
def event_func2():
    print "func2 time:",time.time()
    
def perform2(inc):
    s.enter(inc,0,perform2,(inc,))
    event_func2()
    
def mymain(func,inc=2):
    if func == '1':
        s.enter(0,0,perform1,(5,))#每5秒钟执行perform1
    if func == '2':
        s.enter(0,0,perform2,(10,))#每10秒执行perform2
 
if __name__ == "__main__":
    mymain('1')
    mymain('2')
    s.run()

