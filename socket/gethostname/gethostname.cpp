#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

string Gethostname()
{
	char buf[_SC_HOST_NAME_MAX];
	if (gethostname(buf, sizeof (buf)) < 0) {
		throw runtime_error("gethostname error: "+string(strerror(errno)));
	}
	return buf;
}

int main()
{
    cout << "hostname: " << Gethostname() << endl;
}

