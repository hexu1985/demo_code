#include <QCoreApplication>
#include <thread>
#include "myobject.h"

MyObject *global_object_ptr = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create MyTimer instance
    // QTimer object will be created in the MyTimer constructor
    MyObject my_object;

    global_object_ptr = &my_object;

    QTimer::singleShot(3000, global_object_ptr, SLOT(MyTimerSlot()));

    return a.exec();
}


