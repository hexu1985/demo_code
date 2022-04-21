import threading
import time

def fun_timer():
    print('hello timer')
    global timer
    #重复构造定时器
    timer = threading.Timer(5.8,fun_timer)
    timer.start()
#定时调度
timer = threading.Timer(2,fun_timer)
timer.start()


# 50秒后停止定时器
time.sleep(50)
timer.cancel()
