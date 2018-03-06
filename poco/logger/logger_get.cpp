#include "Poco/Logger.h"  

using Poco::Logger;  

int main(int argc, char** argv)  
{  
    Logger& logger = Logger::get("TestLogger");  
    logger.information("This is an informational message");  
    logger.warning("This is a warning message");  
    return 0;  
}  
