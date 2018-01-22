#include "Poco/Observer.h"
#include "Poco/Task.h"
#include "Poco/Thread.h"
#include "Poco/TaskManager.h"
#include "Poco/TaskNotification.h"
#include <iostream>
 
using Poco::Observer;
using namespace std;
  
class SampleTask: public Poco::Task  
{  
public:  
    SampleTask(const std::string& name): Task(name)  
    {}  
  
  
    void runTask()  
    {  
        for (int i = 0; i < 100; ++i)  
        {  
            setProgress(float(i)/100); // report progress  
            if (sleep(1000))  
                break;  
        }  
    }  
};  
  
class ProgressHandler  
{  
public:  
    void onProgress(Poco::TaskProgressNotification* pNf)  
    {  
        std::cout << pNf->task()->name()  
            << " progress: " << pNf->progress() << std::endl;  
        pNf->release();  
    }  
    void onFinished(Poco::TaskFinishedNotification* pNf)  
    {  
        std::cout << pNf->task()->name() << " finished." << std::endl;  
        pNf->release();  
    }  
};  
  
int main(int argc, char** argv)  
{  
    Poco::TaskManager tm;  
    ProgressHandler pm;  
    tm.addObserver(  
        Observer<ProgressHandler, Poco::TaskProgressNotification>  
        (pm, &ProgressHandler::onProgress)  
        );  
    tm.addObserver(  
        Observer<ProgressHandler, Poco::TaskFinishedNotification>  
        (pm, &ProgressHandler::onFinished)  
        );  
    tm.start(new SampleTask("Task 1")); // tm takes ownership  
    Poco::Thread::sleep(300);
    tm.start(new SampleTask("Task 2"));  
    tm.joinAll();  
    return 0;  
}  
