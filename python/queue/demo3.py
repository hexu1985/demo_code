import queue
import threading
 
xuewei_fans_q = queue.Queue()
 
 
def transfer(money):
    for i in range(100000):
        xuewei_fans_q.put(money)
        xuewei_fans_q.get()
 
 
# 创建4个任务重复给学委加关注/脱粉（还是希望各位编程的明日之星跟着学习，共同进步！）
t_group = []
for i in range(10):
    t = threading.Thread(target=lambda: transfer(-1))
    t_group.append(t)
    t.start()
    t = threading.Thread(target=lambda: transfer(1))
    t_group.append(t)
    t.start()
    t = threading.Thread(target=lambda: transfer(-1))
    t_group.append(t)
    t.start()
    t = threading.Thread(target=lambda: transfer(1))
    t_group.append(t)
    t.start()
 
for t in t_group:
    t.join()

print("-" * 16)
print("活跃线程数:", threading.active_count())
print("活跃线程:", threading.current_thread().name)
#反复对队列进行添加数据，移除数据，队列最后清零了
print("学委粉丝队列:", xuewei_fans_q.qsize())

