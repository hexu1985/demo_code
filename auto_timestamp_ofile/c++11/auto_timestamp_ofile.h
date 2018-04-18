#ifndef __auto_timestamps_ofile_h
#define __auto_timestamps_ofile_h

#include <string>
#include <fstream>

class AutoTimestampOFile {
private:
    std::string prefix_;
    std::string suffix_;
    std::string start_timestamp_;
    std::ofstream ofile_;

public:
    AutoTimestampOFile(const std::string &prefix, const std::string &suffix = "");
    ~AutoTimestampOFile();

    void write(const char *s, int n);
    void flush();
    int size();
};

#endif
