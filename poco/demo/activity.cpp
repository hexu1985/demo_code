#include "Poco/Activity.h"  
#include "Poco/Thread.h"  
#include <iostream>  

using Poco::Thread;  

class ActivityExample  
{  
public:  
      ActivityExample(): _activity(this,   
         &ActivityExample::runActivity)  
      {}  
      void start()  
      {  
           _activity.start();  
      }  
      void stop()  
      {  
           _activity.stop(); // request stop  
           _activity.wait(); // wait until activity actually stops  
      }  
protected:  
      void runActivity()  
     {  
          while (!_activity.isStopped())  
         {  
              std::cout << "bingzhe running." << std::endl;  
              Thread::sleep(200);  
         }  
      }  
private:  
      Poco::Activity<ActivityExample> _activity;  
};  
  
int main(int argc, char** argv)  
{  
      ActivityExample example;  
      example.start();  
      Thread::sleep(2000);  
      example.stop();  
      return 0;  
} 
