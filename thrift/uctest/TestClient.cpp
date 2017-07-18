#include <iostream>
#include <string>
#include <functional>

#include <event.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/async/TAsyncChannel.h>
#include <thrift/async/TEvhttpClientChannel.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "Test.h"

using namespace std;
using namespace std::placeholders;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::async;

using namespace uctest;


void my_ping_pong(TestCobClient* client)
{
	std::string pong;
	client->recv_pingpong(pong);
	printf("[%d] recv:%s\n", (int)time(NULL), pong.c_str());
}

int main(int argc, char **argv) 
{
	try
	{
		event_base* evbase = event_base_new();
		boost::shared_ptr<TAsyncChannel> channel(new TEvhttpClientChannel("127.0.0.1", "/", "127.0.0.1", 9091, evbase));
		TestCobClient client(channel, new TBinaryProtocolFactory());
		function<void(TestCobClient* client)> cob = bind(&my_ping_pong,_1);

		client.pingpong(cob, "ping");
		printf("[%d] ping\n", (int)time(NULL));

		for(int i=0;i<5;i++)
		{
			printf("[%d] running...\n", (int)time(NULL));
			sleep(1);
		}

		event_base_dispatch(evbase);
		event_base_free(evbase);
	}

	catch(...)
	{
		printf("exception");
		return 1;
	}

	return 0;
};
