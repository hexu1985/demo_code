#include "utc_to_string.h"
#include <time.h>
#include <mutex>

using namespace std;
using namespace std::chrono;

namespace {
static mutex g_lock;
}   // 

string utc_to_string(const system_clock::time_point &tp)
{
    char buffer[80];
    time_t tt = system_clock::to_time_t(tp);
    struct tm timeinfo;

    {
        lock_guard<mutex> lck(g_lock);
        struct tm *ptm = gmtime(&tt);
        timeinfo = *ptm;
    } 

    strftime (buffer,80,"%Y%m%d%H%M%S",&timeinfo);

    return string(buffer);
}
