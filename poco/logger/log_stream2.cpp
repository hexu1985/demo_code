#include "Poco/LogStream.h"  
#include "Poco/Logger.h"  
#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"

using Poco::LogStream;  
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
    LogStream lstr(logger);  
    lstr << "This is a test" << std::endl;  
    return 0;  
}  
