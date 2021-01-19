#include "mytimer.h"
#include <QDebug>

MyTimer::MyTimer(): thread("test")
{
    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
          this, SLOT(MyTimerSlot()));

    // msec
    timer->start(3000);
    thread.start();
}

void dowork()
{
  QTimer::singleShot(1000, []{
    qDebug() << "dowork...";
      });
}

void MyTimer::MyTimerSlot()
{
    qDebug() << "Timer...";
    thread.getTaskQueue()->pushTask(&dowork);
}
