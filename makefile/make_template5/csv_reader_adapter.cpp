#include <string>
#include <memory>
#include <vector>

#include "csv_reader_adapter.h"
#include "csv_reader.h"

using namespace std;

vector<PersonPtr> CSVReaderAdapter::readPersons() {
    CSVReader reader;
    vector<string_array_ptr> readPersons = reader.readPersonsFile(file);

    vector<PersonPtr> personsVector;
    for (auto &person_ptr : readPersons) {
        auto &person = *person_ptr;
        personsVector.push_back(PersonPtr(new Person(person[0], person[1])));
    }

    return personsVector;
}
