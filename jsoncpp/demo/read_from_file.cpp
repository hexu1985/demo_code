#include <fstream>
#include <iostream>
#include <string>
#include "json_helper.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " file\n";
        return -1;
    }

    ifstream ifile(argv[1]);
    if (!ifile) {
        cerr << "file " << argv[1] << ", not exists!\n";
        return -2;
    }

    Json::Value json; 
    Json_parse(ifile, &json);

    cout << json["carriorName"].asString() << endl;

	return 0;
}

