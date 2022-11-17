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

sqli="insert into student values(%s,%s,%s,%s)"
cur.execute(sqli, ('3','Tom','1 year 1 class','6'))

cur.close()
conn.commit()
conn.close()
