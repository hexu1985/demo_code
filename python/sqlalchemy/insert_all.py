#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

students = []

session = Session()    #创建session对象
students.append(Student(Sno='10001',Sname='Frank',Ssex='M',Sage=22,Sdept='SFS'))    #数据对象得到创建，此时为Transient状态
students.append(Student(Sno='10002',Sname='Jim',Ssex='M',Sage=19,Sdept='SFS'))    #数据对象得到创建，此时为Transient状态
students.append(Student(Sno='10003',Sname='Tom',Ssex='M',Sage=20,Sdept='SFC'))    #数据对象得到创建，此时为Transient状态
students.append(Student(Sno='10004',Sname='Merry',Ssex='W',Sage=20,Sdept='SFS'))    #数据对象得到创建，此时为Transient状态
students.append(Student(Sno='10005',Sname='Kim',Ssex='M',Sage=21,Sdept='SFC'))    #数据对象得到创建，此时为Transient状态
session.add_all(students)    #数据对象被关联到session上，此时为Pending状态
session.commit()    #数据对象被推到数据库中，此时为Persistent状态
session.close()    #关闭session对象

