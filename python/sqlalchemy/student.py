#coding=utf-8
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import  String,Column,Integer

engine = create_engine("mysql+mysqldb://test:123456@127.0.0.1:3306/flask_DB")
Session = sessionmaker(bind=engine)
Base = declarative_base()

class Student(Base):    #必须继承declaraive_base得到的那个基类
    __tablename__ = "Students"    #必须要有__tablename__来指出这个类对应什么表，这个表可以暂时在库中不存在，SQLAlchemy会帮我们创建这个表
    Sno = Column(String(10),primary_key=True)    #Column类创建一个字段
    Sname = Column(String(20),nullable=False,unique=True,index=True)    #nullable就是决定是否not null，unique就是决定是否unique。。这里假定没人重名，设置index可以让系统自动根据这个字段为基础建立索引
    Ssex = Column(String(2),nullable=False)
    Sage = Column(Integer,nullable=False)
    Sdept = Column(String(20))

    def __repr__(self):
        return "<Student>{}:{}".format(self.Sname,self.Sno)


