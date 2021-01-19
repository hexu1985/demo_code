#include <QCoreApplication>
#include <thread>
#include <iostream>
#include "myobject.h"
#include "qstringevent.h"

MyObject *global_object_ptr = 0;

void thread_func() 
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "postEvent" << std::endl;
    QCoreApplication::sendEvent(global_object_ptr, new QStringEvent("test")); 
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create MyTimer instance
    // QTimer object will be created in the MyTimer constructor
    MyObject my_object;

    global_object_ptr = &my_object;

    std::thread thr(thread_func);

    return a.exec();
}


