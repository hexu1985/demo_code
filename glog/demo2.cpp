#include <iostream>
#include <glog/logging.h>

using namespace std;

int main(int argc, char **argv)
{
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, "log-");

    char str[20] = "hello log!";    
    LOG(INFO) << "Found " << google::COUNTER <<endl;    
    LOG(INFO) << str ;                // << " cookies";    
    LOG(WARNING) << "warning test";    // 会输出一个Warning日志    
    LOG(ERROR) << "error test";        // 会输出一个Error日志 

    return 0;
}
