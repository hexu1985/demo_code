#ifndef __i_person_reader_h
#define __i_person_reader_h

#include <vector>
#include <memory>

#include "person.h"

typedef std::unique_ptr<Person> PersonPtr;

class IPersonsReader {
public:
    virtual std::vector<PersonPtr> readPersons() = 0;
};

#endif
