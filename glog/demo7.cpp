#include <glog/logging.h>

int main(int argc, char* argv[])  
{  
    FLAGS_log_dir = "./log";  
    google::InitGoogleLogging(argv[0]);  

    LOG(INFO) << "INFO";  
    LOG(INFO) << "INFO1";  
    LOG(WARNING) << "WARNING";  
    LOG(WARNING) << "WARNING1";  
    LOG(ERROR) << "ERROR";  
    LOG(ERROR) << "ERROR1";  
    LOG(FATAL) << "FATAL";  

    google::ShutdownGoogleLogging();  
    return 0;  
}  
