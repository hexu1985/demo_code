#include "myobject.h"
#include <QDebug>

MyObject::MyObject()
{
}

void MyObject::MyTimerSlot()
{
    qDebug() << "Timer...";
}
