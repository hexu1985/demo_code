#include "Poco/Logger.h"  
#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"

using Poco::Logger;  
using Poco::AutoPtr;  
using Poco::ConsoleChannel;  

void init_log()
{
    AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
    Logger::root().setChannel(pCons);
}

int main(int argc, char** argv)  
{  
    init_log();

    Logger& logger = Logger::get("TestLogger");  
    logger.information("This is an informational message");  
    logger.warning("This is a warning message");  
    return 0;  
}  
