#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QTimer>

class MyObject : public QObject {
Q_OBJECT
public:
    MyObject();

    void set_signal();

signals:
    void MySignal();

public slots:
    void MySlot();
    void MyTimerSlot();
};

#endif // MYTIME
