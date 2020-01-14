#include <glog/logging.h>
 
int main(int argc, char* argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
 
    LOG(INFO) << "This is an info  message";
    LOG(WARNING) << "This is a warning message";
    LOG(ERROR) << "This is an error message";
    LOG(FATAL) << "This is a fatal message";

    google::ShutDownCommandLineFlags();
 
    return 0;
}
