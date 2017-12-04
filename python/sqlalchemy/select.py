#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

session = Session()    #创建session对象
frank = session.query(Student).filter(Student.Sname == 'Frank').first()
print frank
session.commit()    #数据对象被推到数据库中，此时为Persistent状态
session.close()    #关闭session对象

