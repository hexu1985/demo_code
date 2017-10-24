#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import sys
import getopt
import logging
import MySQLdb

class UidSequenceGenerator:
    def __init__(self, conn):
        self.conn = conn
        cur = conn.cursor()
        
        #创建数据表
        create_tbl_sql = """CREATE TABLE IF NOT EXISTS uid_sequence (  
                                id BIGINT(20) unsigned NOT NULL AUTO_INCREMENT,
                                stub CHAR(1) NOT NULL,  
                                PRIMARY KEY (id),
                                UNIQUE KEY stub(stub)
                                ) ENGINE=MyISAM AUTO_INCREMENT=1"""
        cur.execute(create_tbl_sql)
        cur.close()

    def new_uid(self):
        cur = conn.cursor()

        #生成uid
        cur.execute("REPLACE INTO uid_sequence(stub) VALUES('a')")
        cur.execute("SELECT LAST_INSERT_ID()")
        
        data = cur.fetchone()
        cur.close()
        conn.commit()

        if (data):
            return data[0]
        else:
            return None

if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    logger = logging.debug
    host = 'localhost'
    port = 3306
    user = 'test'
    db = 'test'
    passwd = '123456'

    try:
        options, remainder = getopt.getopt(
                sys.argv[1:],
                'h',
                ['help', 'host=', 'user=', 'port=', 'passwd=', 'db=']
                )
    except getopt.GetoptError as err:
        print 'ERROR:', err
        sys.exit(1)

    logger('OPTIONS : %s' % options)

    for opt, arg in options:
        if opt == '--host':
            host = arg
        elif opt == '--user':
            user = arg
        elif opt == '--port':
            port = int(arg)
        elif opt == '--passwd':
            passwd = arg
        elif opt == '--db':
            db = arg
        elif opt in ('-h', '--help'):
            print "usage: %s [--host host] [--user user] [--port port] [--passwd passwd] [--db db] " % sys.argv[0]
            sys.exit(1)

    logger('host    : %s' % host)
    logger('port    : %s' % port)
    logger('user    : %s' % user)
    logger('passwd  : %s' % passwd)
    logger('db      : %s' % db)

    conn = MySQLdb.connect(
        host=host,
        port=port,
        user=user,
        passwd=passwd,
        db=db
        )

    uid_gen = UidSequenceGenerator(conn)
    i = 0
    while i < 10:
        print "id: %s" % uid_gen.new_uid()
        i += 1
