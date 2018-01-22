#include "Poco/Process.h" 
#include "Poco/PipeStream.h" 
#include "Poco/StreamCopier.h" 
#include <fstream> 

using Poco::Process; 
using Poco::ProcessHandle; 

int main(int argc, char** argv) 
{ 
    std::string cmd("/bin/ps"); 
    std::vector<std::string> args; 
    args.push_back("-ax"); 
    Poco::Pipe outPipe; 
    ProcessHandle ph = Process::launch(cmd, args, 0, &outPipe, 0); 
    Poco::PipeInputStream istr(outPipe); 
    std::ofstream ostr("processes.txt"); 
    Poco::StreamCopier::copyStream(istr, ostr); 
    return 0; 
} 
