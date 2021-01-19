#include <QCoreApplication>
#include <thread>
#include <iostream>
#include "myobject.h"

MyObject *global_object_ptr = 0;

void thread_func() 
{
    std::cout << " current thread id: " << std::this_thread::get_id() << std::endl;
    global_object_ptr->set_signal(); 
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << " main thread id: " << std::this_thread::get_id() << std::endl;

    // Create MyTimer instance
    // QTimer object will be created in the MyTimer constructor
    MyObject my_object;

    global_object_ptr = &my_object;

    std::thread thr(thread_func);

    return a.exec();
}


