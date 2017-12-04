#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

session = Session()    #创建session对象
frank = Student(Sno='10001',Sname='Frank',Ssex='M',Sage=22,Sdept='SFS')    #数据对象得到创建，此时为Transient状态
session.add(frank)    #数据对象被关联到session上，此时为Pending状态
session.commit()    #数据对象被推到数据库中，此时为Persistent状态
session.close()    #关闭session对象

