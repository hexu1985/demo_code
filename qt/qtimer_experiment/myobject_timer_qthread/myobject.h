#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QTimer>

class MyObject : public QObject {
Q_OBJECT
public:
    MyObject();

public slots:
    void MyTimerSlot();
};

#endif // MYTIME
