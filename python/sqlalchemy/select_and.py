#coding=utf-8
from sqlalchemy import and_,or_
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

session = Session()    #创建session对象
print session.query(Student).filter(and_(Student.Sdept == 'SFS' , Student.Sage < 22)).all()
session.commit()    #数据对象被推到数据库中，此时为Persistent状态
session.close()    #关闭session对象

