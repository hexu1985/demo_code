#coding=utf-8
import MySQLdb

conn= MySQLdb.connect(
        host='127.0.0.1',
        port = 3306,
        user='root',
        passwd='123456',
        db ='test',
        )
cur = conn.cursor()

#获得表中有多少条数据
aa=cur.execute("select * from student")
print(aa)

#打印表中的多少数据
info = cur.fetchmany(aa)
for ii in info:
    print(ii)
cur.close()
conn.commit()
conn.close()
