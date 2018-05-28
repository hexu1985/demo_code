#include <fstream>
#include <iostream>
#include <string>
#include "json11.hpp"

using namespace std;
using namespace json11;

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

    istreambuf_iterator<char>  beg(ifile),  end;    
    string str(beg,  end);
    string err;

    auto json = Json::parse(str, err);

    if (!err.empty()) {
        cout << "parse json error: " << err << endl;
    }

    cout << json["carriorName"].string_value() << endl;
    cout << str << endl;

	return 0;
}

