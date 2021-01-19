#include "myobject.h"
#include "qstringevent.h"
#include <QDebug>
#include <iostream>

MyObject::MyObject()
{
}

void MyObject::MyTimerSlot()
{
    qDebug() << "Timer...";
}

bool MyObject::eventFilter(QObject *target, QEvent *event)
{
    qDebug() << "eventFilter...";
    if (target == this && event->type() == QStringEvent::TYPE) {
        std::cout << "QTimer::singleShot:" << std::endl; 
        QTimer::singleShot(1000, this, SLOT(MyTimerSlot()));
    }

    return QObject::eventFilter(target, event);
}
