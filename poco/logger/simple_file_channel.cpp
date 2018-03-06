#include "Poco/Logger.h"  
#include "Poco/SimpleFileChannel.h"  
#include "Poco/AutoPtr.h"  

using Poco::Logger;  
using Poco::SimpleFileChannel;  
using Poco::AutoPtr;  

int main(int argc, char** argv)  
{  
    AutoPtr<SimpleFileChannel> pChannel(new SimpleFileChannel);  
    pChannel->setProperty("path", "sample.log");  
    pChannel->setProperty("rotation", "2 K");  
    Logger::root().setChannel(pChannel);  
    Logger& logger = Logger::get("TestLogger"); // inherits root channel  
    for (int i = 0; i < 100; ++i)  
        logger.information("Testing SimpleFileChannel");  
    return 0;  
}  
