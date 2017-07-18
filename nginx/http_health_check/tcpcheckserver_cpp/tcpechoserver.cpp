/* include fig01 */
#include <iostream>
#include <string>
#include "error.h"
#include "wrapunix.h"
#include "writen.h"
#include "tcpserver.h"

using namespace std;

class TcpEchoHandler: public TcpConnectionHandler {
public:
    bool setup(int sockfd) override
    {
        cout << __func__ << ", fd=" << sockfd << endl;
        return true;
    }

    bool handle(int sockfd) override
    {
        cout << __func__ << ", fd=" << sockfd << endl;
        char buffer[1024];
        int n = Read(sockfd, buffer, sizeof(buffer));
        Writen(sockfd, buffer, n);
        return true;
    }

    // 当sockfd已经被setup成功后, sockfd被close时调用
    void finish(int sockfd) override
    {
        cout << __func__ << ", fd=" << sockfd << endl;
    }
};

int
main(int argc, char **argv)
{
    string listen_host;
    int listen_port;

	if (argc == 2) {
        listen_port = stoi(string(argv[1]));
    } else if (argc == 3) {
        listen_host = argv[1];
        listen_port = stoi(string(argv[2]));
    } else {
		err_quit("usage: daytimetcpsrv4 [ <host> ] <service or port>");
    }

    TcpServer tcpserver;

    tcpserver.add_handler(listen_host, listen_port, std::make_shared<TcpEchoHandler>());
    tcpserver.start();

    char c;
    cout << "entry any key to stop" << endl;
    cin >> c;

    return 0;
}
/* end fig02 */
