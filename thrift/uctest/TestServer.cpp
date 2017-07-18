#include <stdio.h>
#include <string>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/THttpServer.h>

#include "Test.h"

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace uctest;


class TestHandler: virtual public TestIf {
public:
	TestHandler() { }

	void pingpong(std::string& _return, const std::string& data) 
	{
		if(data=="ping")
			printf("[%d] recv ping\n", (int)time(NULL));
		_return = "pong";
		printf("[%d] send pong\n", (int)time(NULL));
	}
};

int main(int argc, char **argv) 
{
	int port = 9091;

	boost::shared_ptr<TestHandler> handler(new TestHandler());
	boost::shared_ptr<TProcessor> processor(new TestProcessor(handler));
	boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	boost::shared_ptr<TTransportFactory> transportFactory(new THttpServerTransportFactory());
	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();

	return 0;
}

