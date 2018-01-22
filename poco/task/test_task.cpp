#include <iostream>  
#include <stdio.h>  
#include <Poco/Util/TimerTask.h>  
#include <Poco/Util/Timer.h>  
#include <Poco/Task.h>  
#include <Poco/Timestamp.h>  
#include <Poco/Runnable.h>  
#include <Poco/Thread.h>  
  
using namespace std;  
  
//Poco Pthread  
class TestPthread:public Poco::Runnable  
{  
public:  
    void run();  
};  
  
void TestPthread::run()  
{  
    while(1) {  
        cout<<"TestPthread::run test"<<endl;  
        Poco::Thread::sleep(1000);  
    }  
}  
  
  
//Poco Task  
class TestTask:public Poco::Task  
{  
public:  
    TestTask(std::string str):Task(str){}  
    void runTask();  
};  
  
void TestTask::runTask()  
{  
    while(!isCancelled()) {  
        cout<<"TestTask::run test"<<endl;  
        Poco::Thread::sleep(1000);  
    }  
}  
  
int main()  
{  
      
    Poco::Thread pid;  
    /*test Pthread*/  
    //TestPthread obj;  
    //pid.start(obj);  
  
    /*test Task*/  
    TestTask taskobj("123");  
    pid.start(taskobj);  
    Poco::Thread::sleep(3000);  
    taskobj.cancel();  
    getchar();  
    return 0;  
}  
