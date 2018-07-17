#include <thread>
#include <string>
#include <fstream>
#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include "error.h"
#include "tcp_listen.h"
#include "wrapsock.h"
#include "sock_ntop.h"
#include "sock_ntop_host.h"
#include "sock_get_port.h"
#include "utc_to_string.h"

#define MAXLINE 8192

using namespace std;

string gen_file_name(const string &prefix, const string &suffix, const SA *cliaddr, socklen_t len)
{
    string host = Sock_ntop_host(cliaddr, len);
    int port = sock_get_port(cliaddr, len);
    return prefix + "_" + host + "_" + to_string(port) + "_" + utc_to_string(chrono::system_clock::now()) + "." + suffix;
}

void do_log(string file_name, int sockfd)
{
    ofstream ofile(file_name);
    if (!ofile) {
        cerr << "open file error: " << file_name << "\n";
        goto done;
    }

    ssize_t n;
    char buf[MAXLINE];

again:
    while ( (n = read(sockfd, buf, MAXLINE)) > 0) {
		ofile.write(buf, n);
	}

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_ret("str_echo: read error");

done:
    cout << "file close: " << file_name << endl;
    close(sockfd);
}

int
main(int argc, char **argv)
{
	int listenfd = -1;

	if (argc == 2)
		listenfd = Tcp_listen(nullptr, argv[1]);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2]);
	else
		err_quit("usage: tcplog_server [ <host> ] <port#>");

	struct sockaddr_storage	cliaddr;

	for ( ; ; ) {
		socklen_t len = sizeof(cliaddr);
		int connfd = Accept(listenfd, (SA *)&cliaddr, &len);
        cout << "connection from " << Sock_ntop((SA *)&cliaddr, len) << endl;

        string file_name = gen_file_name("log", "txt", (SA *)&cliaddr, len);
        thread thr(do_log, file_name, connfd);
        thr.detach();
	}
}

