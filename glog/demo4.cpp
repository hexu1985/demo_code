#include <glog/logging.h>
#include <glog/raw_logging.h>

class GLogHelper {
public:
    GLogHelper(char*program)
    {
        google::InitGoogleLogging(program);
        FLAGS_stderrthreshold = google::INFO;
        FLAGS_colorlogtostderr = true;
        FLAGS_v = 3;
    }

    ~GLogHelper()
    {
        google::ShutdownGoogleLogging();
    }
};

int main(int argc,char* argv[])
{
    GLogHelper gh(argv[0]);

    LOG(ERROR) <<"LOG";
    VLOG(3) <<"VLOG";
    DLOG(ERROR) <<"DLOG";
    DVLOG(3) <<"DVLOG";
    SYSLOG(ERROR) <<"SYSLOG";
    PLOG(ERROR) <<"PLOG";
    RAW_LOG(ERROR,"RAW_LOG");

    return 0;
}
