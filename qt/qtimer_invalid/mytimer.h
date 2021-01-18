#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include "WorkerThread.hpp"

class MyTimer : public QObject {
Q_OBJECT
public:
    MyTimer();
    QTimer *timer;

    mini_utils::WorkerThread thread;

public slots:
    void MyTimerSlot();
};

#endif // MYTIME
