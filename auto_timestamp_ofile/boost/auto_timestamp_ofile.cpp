#include "auto_timestamp_ofile.h"
#include <stdio.h>
#include <stdexcept>
#include "boost/chrono.hpp"

#include "utc_to_string.h"

using namespace std;
using namespace boost::chrono;

AutoTimestampOFile::AutoTimestampOFile(const string &prefix, const string &suffix) 
    : prefix_(prefix), suffix_(suffix)
{
    system_clock::time_point tp = system_clock::now();
    start_timestamp_ = utc_to_string(tp);
    string filename = prefix_+start_timestamp_+"-"+suffix_;
    ofile_.open(filename.c_str());
    if (!ofile_)
        throw std::runtime_error("open file "+filename+" fail");
}

AutoTimestampOFile::~AutoTimestampOFile() 
{
    try {
        ofile_.close();
        system_clock::time_point tp = system_clock::now();
        string stop_timestamp = utc_to_string(tp);
        string oldname = prefix_+start_timestamp_+"-"+suffix_;
        string newname = prefix_+start_timestamp_+"-"+stop_timestamp+suffix_;
        rename(oldname.c_str(), newname.c_str());
    } catch (...) {
        // todo
    }
}

void AutoTimestampOFile::write(const char *s, int n)
{
    ofile_.write(s, n);
}

void AutoTimestampOFile::flush()
{
    ofile_.flush();
}

int AutoTimestampOFile::size()
{
    return ofile_.tellp();
}

