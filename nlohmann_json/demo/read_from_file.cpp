#include <fstream>
#include <iostream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;
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

	json js;
	ifile >> js;

    cout << js["carriorName"].get<string>() << endl;
    cout << setw(4) << js << endl;

	return 0;
}

