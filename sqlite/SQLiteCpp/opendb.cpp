#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++) {
		try {
        	SQLite::Database mDb(argv[i]);    ///< Database open
        	cout << "open " << argv[i] << " ok" << endl;
		} catch (const SQLite::Exception &e) {
			cout << "open " << argv[i] << " error: " << e.getErrorCode() << ", " << e.what() << endl;
		}
    }

    return 0;
}
