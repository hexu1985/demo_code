#coding=utf-8
import MySQLdb

conn= MySQLdb.connect(
        host='localhost',
        port = 3306,
        user='root',
        passwd='123456',
        db ='test',
        )
cur = conn.cursor()

#创建数据表
try:
    cur.execute("drop table student")
except:
    pass
cur.execute("create table student(id int ,name varchar(20),class varchar(30),age varchar(10))")

cur.close()
conn.commit()
conn.close()
