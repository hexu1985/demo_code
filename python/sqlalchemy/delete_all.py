#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

session = Session()    #创建session对象
session.query(Student).delete()
session.commit()
session.close()    #关闭session对象
