#include "UserService.h"  
#include <thrift/config.h>  
#include <thrift/protocol/TBinaryProtocol.h>  
#include <thrift/protocol/TCompactProtocol.h>  
#include <thrift/server/TSimpleServer.h>  
#include <thrift/transport/TServerSocket.h>  
#include <thrift/transport/TBufferTransports.h>  
#include <thrift/concurrency/ThreadManager.h>  
#include <thrift/concurrency/PosixThreadFactory.h>  
#include <thrift/server/TThreadPoolServer.h>  
#include <thrift/server/TThreadedServer.h>  

using namespace ::apache::thrift;  
using namespace ::apache::thrift::protocol;  
using namespace ::apache::thrift::transport;  
using namespace ::apache::thrift::server;  
using namespace ::apache::thrift::concurrency;  

using boost::shared_ptr;  

class UserServiceHandler : virtual public UserServiceIf {  
public:  
	UserServiceHandler() {  
		// Your initialization goes here  
	}  

	void add(const User& u) {  
		// Your implementation goes here  
		printf("uid=%s uname=%s usex=%d uage=%d\n", u.uid.c_str(), u.uname.c_str(), u.usex, u.uage);  
	}  

	void get(User& _return, const std::string& uid) {  
		// Your implementation goes here  
		_return.uid = "leo1";  
		_return.uname = "yueyue";  
		_return.usex = 1;  
		_return.uage = 3;  
		printf("uid=%s uname=%s usex=%d uage=%d\n", _return.uid.c_str(), _return.uname.c_str(), _return.usex, _return.uage);  
	}  
};  

int main(int argc, char **argv) {  
	shared_ptr<UserServiceHandler> handler(new UserServiceHandler());  
	shared_ptr<TProcessor> processor(new UserServiceProcessor(handler));  
	shared_ptr<TProtocolFactory> protocolFactory(new TCompactProtocolFactory());  
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());  
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));  

	shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(10);  
	shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());  
	threadManager->threadFactory(threadFactory);  
	threadManager->start();  
	printf("start user server...\n");  

	TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);  
	server.serve();  
	return 0;  
}  
