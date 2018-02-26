#include "Poco/Logger.h"  
#include "Poco/AsyncChannel.h"  
#include "Poco/ConsoleChannel.h"  
#include "Poco/AutoPtr.h"  

using Poco::Logger;  
using Poco::AsyncChannel;  
using Poco::ConsoleChannel;  
using Poco::AutoPtr;  

int main(int argc, char** argv)  
{  
    AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);  
    AutoPtr<AsyncChannel> pAsync(new AsyncChannel(pCons));  
    Logger::root().setChannel(pAsync);  
    Logger& logger = Logger::get("TestLogger");  
    for (int i = 0; i < 10; ++i)  
        logger.information("This is a test");  
    return 0;  
}  
