import queue
 
q = queue.Queue(5)
 
print("学委粉丝队列：", q)
print("空队，学委粉丝队列大小：", q.qsize())
print("空队列？", q.empty())
for i in range(5):
    q.put(i)
 
print("队列满了？", q.full())
print("排满了，学委粉丝队列大小：", q.qsize())
 
while not q.empty():
    print("粉丝 %s 出队点赞！" % q.get())
print("最后，学委粉丝队列大小：", q.qsize())
