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

#创建数据表
create_tbl_sql = """CREATE TABLE IF NOT EXISTS uid_sequence (  
                        id BIGINT(20) unsigned NOT NULL AUTO_INCREMENT,
                        stub CHAR(1) NOT NULL,  
                        PRIMARY KEY (id),
                        UNIQUE KEY stub(stub)
                        ) ENGINE=MyISAM AUTO_INCREMENT=1"""
cur.execute(create_tbl_sql)

#生成uid
cur.execute("REPLACE INTO uid_sequence(stub) VALUES('a')")
cur.execute("SELECT LAST_INSERT_ID()")

data = cur.fetchone()
if (data):
    print data
else:
    print "no data"

cur.close()
conn.commit()
conn.close()
