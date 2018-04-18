#include "auto_timestamp_ofile.h"
#include <stdio.h>
#include <stdexcept>
#include "boost/chrono.hpp"

#include "utc_to_string.h"

using namespace std;
using namespace boost::chrono;

AutoTimestampOFile::AutoTimestampOFile(const string &prefix, const string &extension) 
    : prefix_(prefix), extension_(extension)
{
    system_clock::time_point tp = system_clock::now();
    start_timestamp_ = utc_to_string(tp);
    string filename = prefix_+start_timestamp_+"-"+extension_;
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
        string oldname = prefix_+start_timestamp_+"-"+extension_;
        string newname = prefix_+start_timestamp_+"-"+stop_timestamp+extension_;
        rename(oldname.c_str(), newname.c_str());
    } catch (...) {
        // todo
    }
}

void AutoTimestampOFile::write(const char *s, int n)
{
    ofile_.write(s, n);
}

size_t AutoTimestampOFile::size()
{
    return ofile_.tellp();
}

