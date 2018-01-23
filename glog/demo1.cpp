#include <glog/logging.h>

int main(int argc,char* argv[])
{
    google::InitGoogleLogging(argv[0]); //初始化 glog
    LOG(INFO) << "Hello,GOOGLE!";
}
