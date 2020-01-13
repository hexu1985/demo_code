#include <glog/logging.h>
#include <string>
#include <fstream>

//将信息输出到单独的文件和LOG(ERROR)
void SignalHandle(const char* data, int size)
{
    std::ofstream fs("glog_dump.log",std::ios::app);
    std::string str = std::string(data,size);
    fs << str;
    fs.close();
    LOG(ERROR) << str;
}

class GLogHelper {
public:
    GLogHelper(char*program)
    {
        google::InitGoogleLogging(program);
        FLAGS_colorlogtostderr=true;
        google::InstallFailureSignalHandler();

        //默认捕捉 SIGSEGV 信号信息输出会输出到stderr，可以通过下面的方法自定义输出方式：
        google::InstallFailureWriter(&SignalHandle);
    }

    ~GLogHelper()
    {
        google::ShutdownGoogleLogging();
    }
};

void fun()
{
    int* pi = new int;
    delete pi;

    pi = 0;
    int j = *pi;
}

int main(int argc,char* argv[])
{
    GLogHelper gh(argv[0]);

    fun();

    return 0;
}
