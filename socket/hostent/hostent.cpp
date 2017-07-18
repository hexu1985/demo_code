#include <arpa/inet.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using namespace std;

struct hostent *Gethostbyname(const char *hostname)
{
	struct hostent *hptr;
	if ((hptr = gethostbyname(hostname)) == NULL) {
		throw runtime_error("gethostbyname error for "+string(hostname)+": "+
				string(hstrerror(h_errno)));
	}
	return hptr;
}

int main(int argc, char **argv)
{
	char **pptr = NULL;

	if (argc != 2) {
		cerr << "usage: hostent <host>\n";
		exit(1);
	}

	struct hostent	*hptr = Gethostbyname(argv[1]);
	cout << "official hostname: " << hptr->h_name << '\n';
	for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		cout << "\talias: " << *pptr << '\n';

	switch (hptr->h_addrtype) {
	case AF_INET:
		pptr = hptr->h_addr_list;
		for ( ; *pptr != NULL; pptr++)
			cout << "\taddress: " << inet_ntoa(*((struct in_addr *)*pptr)) << '\n';
		break;

	default:
		cerr << "unknown address type\n";
		break;
	}

	return 0;
}
