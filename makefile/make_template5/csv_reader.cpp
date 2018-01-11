#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "csv_reader.h"

using namespace std;

namespace {

void split(const string &s, char c, vector<string> &v) {
    int i = 0;
    int j = s.find(c);

    while (j >= 0) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j < 0) {
            v.push_back(s.substr(i, s.length()));
        }
    }
}

}   // namespace


vector<string_array_ptr> CSVReader::readPersonsFile(const string &file) {
    vector<string_array_ptr> persons;

    ifstream in(file);
    if (!in) {
        cout << "read csv file \"" << file << "\" error!\n";
        return persons;
    }

    string strLine;
    while (getline(in, strLine, '\n')) {
        vector<string> splitted;
        split(strLine, ',', splitted);

        if (splitted.size() >= 2) {
            persons.push_back(string_array_ptr(new vector<string>{splitted[0], splitted[1]}));
        }

        strLine.clear();
    }

    return persons;
}

