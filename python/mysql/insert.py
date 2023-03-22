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

sqli="insert into %s values(%s,%s,%s,%s)"
cur.execute(sqli, ('student', '3','Tom','1 year 1 class','6'))

cur.close()
conn.commit()
conn.close()
