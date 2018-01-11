#ifndef __csv_reader_adapter_h
#define __csv_reader_adapter_h

#include <string>
#include <memory>
#include <vector>

#include "i_persons_reader.h"
#include "person.h"

class CSVReaderAdapter: public IPersonsReader {
private:
    std::string file;

public:
    CSVReaderAdapter(const std::string &file) {
        this->file = file;
    }

    std::vector<std::unique_ptr<Person>> readPersons() override;
};

#endif
