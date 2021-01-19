#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <iostream>
#include "myobject.h"

MyObject *global_object_ptr = 0;

class MyThread : public QThread {
public:
    MyThread();
    ~MyThread();

protected:
    void run() override;
};

MyThread::MyThread()
{
 
}
 
MyThread::~MyThread()
{
}

void thread_func() 
{
    std::cout << "QTimer::singleShot:" << std::endl; 
    QTimer::singleShot(3000, global_object_ptr, SLOT(MyTimerSlot()));
}

void MyThread::run()
{
    qDebug()<<"myThread run() start to execute";
    qDebug()<<"     current thread ID:"<<QThread::currentThreadId()<<'\n';
		thread_func();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"     main thread ID:"<<QThread::currentThreadId()<<'\n';

    // Create MyTimer instance
    // QTimer object will be created in the MyTimer constructor
    MyObject my_object;

    global_object_ptr = &my_object;

    MyThread thr;
		thr.start();

    return a.exec();
}


