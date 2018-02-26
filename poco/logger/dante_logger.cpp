#include "dante_logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"

using namespace Poco;

void Logger_initiation()
{
    AutoPtr<FileChannel> file_channel(new FileChannel());
    file_channel->setProperty("rotation" ,"10M");
    file_channel->setProperty("archive" ,"timestamp");
    file_channel->setProperty("path" ,"dante_route_log.log");
    AutoPtr<PatternFormatter> pattern_formatter (new PatternFormatter("%L%H:%M:%S-code line :%u-%U : %t"));
    AutoPtr<FormattingChannel> formatter_channle(new FormattingChannel(pattern_formatter , file_channel));
    Logger::root().setChannel(formatter_channle);           
    ///- finish logger initiation
}

void Setup_logger()
{
    static bool b_setup =false;     // only allow run once time 
    if (! b_setup)
    {
        b_setup =true;  
        Logger_initiation();
    }
}
