#include "myobject.h"
#include <QDebug>
#include <thread>
#include <iostream>

MyObject::MyObject()
{
    // setup signal and slot
    connect(this, SIGNAL(MySignal()),
          this, SLOT(MySlot()), Qt::QueuedConnection);
}

void MyObject::set_signal()
{
    emit MySignal();
}

void MyObject::MySlot()
{
    qDebug() << "MySlot...";
    std::cout << " current thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "QTimer::singleShot:" << std::endl; 
    QTimer::singleShot(3000, this, SLOT(MyTimerSlot()));
}

void MyObject::MyTimerSlot()
{
    qDebug() << "Timer...";
    std::cout << " current thread id: " << std::this_thread::get_id() << std::endl;
}
