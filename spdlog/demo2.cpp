#include <iostream>
#include "spdlog/async.h" //support for async logging.
#include "spdlog/sinks/basic_file_sink.h"

int main(int, char* [])
{
	try
	{        
		auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "logs/async_log.txt");
		for (int i = 1; i < 101; ++i)
		{
			async_file->info("Async message #{}", i);
		}
		// Under VisualStudio, this must be called before main finishes to workaround a known VS issue
		spdlog::drop_all(); 
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log initialization failed: " << ex.what() << std::endl;
	}
}
