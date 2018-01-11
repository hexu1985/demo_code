#include <vector>
#include <memory>
#include "person.h"
#include "i_persons_reader.h"
#include "csv_reader_adapter.h"

using namespace std;

int main(int argc, char *argv[]) {
    unique_ptr<IPersonsReader> reader(new CSVReaderAdapter("persons.csv"));
    vector<PersonPtr> persons = reader->readPersons();

    for (auto &person : persons) {
        person->print();
    }

    return 0;
}
