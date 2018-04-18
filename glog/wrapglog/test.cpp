#include "wrapglog.h"
#include <glog/logging.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string data(80, 'a');

    Glog_init_logging("./log", argv[0]);
    Glog_set_max_log_size(1);
    for (int j = 1; j < 10; j++) {
        for (int i = 1; i < 3000; i++) {
            LOG(INFO) << "(" << i << ") " << data;
        }
        sleep(1);
    }

    Glog_shutdown_logging();

    return 0;
}

