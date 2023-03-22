# -*- coding: UTF-8 -*-

import MySQLdb

# 打开数据库连接
conn= MySQLdb.connect(
        host='127.0.0.1',
        port = 3306,
        user='root',
        passwd='123456',
        db ='test',
        )

# 使用cursor()方法获取操作游标 
cur = conn.cursor()

kId = 0
kName = 1
kClass = 2
kAge = 3

#desc_dict = {kId: "id", kName: "name", kClass: "class", kAge: "age"}
# 使用execute方法执行SQL语句
cur.execute("select id, name, class, age from student")

# 使用 fetchone() 方法获取一条数据库。
while True:
    data = cur.fetchone()
    if (data):
        print("data: ")
        print("\tid: %s" % data[kId])
        print("\tname: %s" % data[kName])
        print("\tclass: %s" % data[kClass])
        print("\tage: %s" % data[kAge])
    else:
        break

# 关闭数据库连接
conn.close()
