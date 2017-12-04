#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

session = Session()    #创建session对象
target = session.query(Student).get("10001")
session.delete(target)
session.commit()
session.close()    #关闭session对象
