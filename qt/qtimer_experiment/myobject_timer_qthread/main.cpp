#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <iostream>
#include "myobject.h"

MyObject *global_object_ptr = 0;

class MyThread : public QThread {
    Q_OBJECT
public:
    MyThread(QObject* parent = nullptr);

#if 0
    //自定义发送的信号
signals:
    void myThreadSignal(const int);
    //自定义槽
public slots:
    void myThreadSlot(const int);
#endif

protected:
    void run() override;
};

MyThread::MyThread(QObject *parent)
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

    // Create MyTimer instance
    // QTimer object will be created in the MyTimer constructor
    MyObject my_object;

    global_object_ptr = &my_object;

    Thread thr(nullptr);
		thr.start();

    return a.exec();
}


