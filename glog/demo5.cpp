#include <glog/logging.h>
#include <string>
#include <fstream>

class GLogHelper {
public:
    GLogHelper(char*program)
    {
        google::InitGoogleLogging(program);
        FLAGS_stderrthreshold = google::INFO;
        FLAGS_colorlogtostderr=true;
        google::InstallFailureSignalHandler();
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
