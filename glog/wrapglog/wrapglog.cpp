#include "wrapglog.h"
#include "glog/logging.h"

void Glog_init_logging(const char *dir, char *prefix)
{
    FLAGS_log_dir = dir;
    google::InitGoogleLogging(prefix);
}

void Glog_set_max_log_size(int nMB)
{
    FLAGS_max_log_size = nMB;
}

int Glog_get_max_log_size()
{
    return FLAGS_max_log_size;
}

void Glog_stop_logging_if_full_disk()
{
    FLAGS_stop_logging_if_full_disk = true;
}

bool Glog_is_stop_logging_if_full_disk()
{
    return FLAGS_stop_logging_if_full_disk;
}

void Glog_shutdown_logging()
{
    google::ShutdownGoogleLogging();
}
