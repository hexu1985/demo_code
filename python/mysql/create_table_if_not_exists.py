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
cur.execute("create table if not exists student(id int ,name varchar(20),class varchar(30),age varchar(10))")

cur.close()
conn.commit()
conn.close()