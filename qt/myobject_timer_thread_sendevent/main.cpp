#include <QCoreApplication>
#include <thread>
#include <iostream>
#include "myobject.h"

MyObject *global_object_ptr = 0;

void thread_func() 
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "QTimer::singleShot:" << std::endl; 
    QTimer::singleShot(3000, global_object_ptr, SLOT(MyTimerSlot()));
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


