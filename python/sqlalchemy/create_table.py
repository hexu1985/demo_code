#coding=utf-8
import student

engine = student.engine
Session = student.Session
Base = student.Base

Base.metadata.create_all(engine)    #这就是为什么表类一定要继承Base，因为Base会通过一些方法来通过引擎初始化数据库结构。不继承Base自然就没有办法和数据库发生联系了。

session = Session()    #实例化了一个会话（或叫事务），之后的所有操作都是基于这个对象的

#既然是事务对象，session必然有以下这些方法
session.commit()    #提交会话（事务）
session.rollback()    #回滚会话
session.close()    #关闭会话
