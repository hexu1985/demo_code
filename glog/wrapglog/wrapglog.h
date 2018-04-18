#ifndef __wrapglog_h
#define __wrapglog_h

void Glog_init_logging(const char *dir, char *prefix);
void Glog_set_max_log_size(int nMB);
int Glog_get_max_log_size();
void Glog_stop_logging_if_full_disk();
bool Glog_is_stop_logging_if_full_disk();
void Glog_shutdown_logging();

#endif
