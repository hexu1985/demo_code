#coding=utf-8
import MySQLdb

conn= MySQLdb.connect(
        host='127.0.0.1',
        port = 3306,
        user='root',
        passwd='123456',
        db ='test',
        )
conn.set_character_set('utf8')

cur = conn.cursor()
cur.execute('SET NAMES utf8')
cur.execute('SET CHARACTER SET utf8')
cur.execute('SET character_set_connection=utf8')

#创建数据表
try:
    cur.execute("drop table student")
except:
    pass
cur.execute("create table student(id int ,name varchar(20),class varchar(30),age varchar(10)) character set = utf8")

#一次插入多条记录
sqli="insert into student values(%s,%s,%s,%s)"
cur.executemany(sqli,[
    ('3',u'汤姆','1 year 1 class','6'),
    ('3',u'杰克','2 year 1 class','7'),
    ('3',u'大卫','2 year 2 class','7'),
    ])

cur.close()
conn.commit()
conn.close()
