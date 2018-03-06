#include "Poco/LogStream.h"  
#include "Poco/Logger.h"  

using Poco::Logger;  
using Poco::LogStream;  

int main(int argc, char** argv)  
{  
    Logger& logger = Logger::get("TestLogger");  
    LogStream lstr(logger);  
    lstr << "This is a test" << std::endl;  
    return 0;  
}  
