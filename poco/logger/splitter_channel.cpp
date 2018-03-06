#include "Poco/Logger.h"  
#include "Poco/SplitterChannel.h"  
#include "Poco/ConsoleChannel.h"  
#include "Poco/SimpleFileChannel.h"  
#include "Poco/AutoPtr.h"  

using Poco::Logger;  
using Poco::SplitterChannel;  
using Poco::ConsoleChannel;  
using Poco::SimpleFileChannel;  
using Poco::AutoPtr;  

int main(int argc, char** argv)  
{  
	AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);  
	AutoPtr<SimpleFileChannel> pFile(new SimpleFileChannel("test.log"));  
	AutoPtr<SplitterChannel> pSplitter(new SplitterChannel);  
	pSplitter->addChannel(pCons);  
	pSplitter->addChannel(pFile);  
	Logger::root().setChannel(pSplitter);  
	Logger::root().information("This is a test");  
	return 0;  
}  
