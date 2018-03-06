#include "Poco/Logger.h"  
#include "Poco/FileChannel.h"  
#include "Poco/AutoPtr.h"  

using Poco::Logger;  
using Poco::FileChannel;  
using Poco::AutoPtr;  

int main(int argc, char** argv)  
{  
    AutoPtr<FileChannel> pChannel(new FileChannel);  
    pChannel->setProperty("path", "sample.log");  
    pChannel->setProperty("rotation", "2 K");  
    pChannel->setProperty("archive", "timestamp");  
    pChannel->setProperty("purgeCount", "3");  
    Logger::root().setChannel(pChannel);  
    Logger& logger = Logger::get("TestLogger"); // inherits root channel  
    for (int i = 0; i < 10000; ++i)  
        logger.information("Testing FileChannel");  

    return 0;  
}  
