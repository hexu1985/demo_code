#ifndef __csv_reader_h
#define __csv_reader_h

#include <vector>
#include <string>
#include <memory>

typedef std::unique_ptr<std::vector<std::string>> string_array_ptr;

class CSVReader {
public:
    std::vector<string_array_ptr> readPersonsFile(const std::string &file);
};

#endif
