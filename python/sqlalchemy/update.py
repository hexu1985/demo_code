#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base
Student = student.Student

session = Session()    #创建session对象
target = session.query(Student).filter(Student.Sname == "Kim").first()
target.Sname = "Kimmy"
session.commit()
session.close()

##之后在到数据库后台，或者这里查询看到的就是Kimmy了
print session.query(Student).filter_by(Sname="Kimmy").first()    #有结果
