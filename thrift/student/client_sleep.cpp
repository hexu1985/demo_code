#include "Serv.h"  // 替换成你的.h  
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;

int main()
{
	boost::shared_ptr<TSocket> socket(new TSocket("127.0.0.1", 9090));
	
	//对接nonblockingServer时必须的，对普通server端时用boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket)); 
	
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	ServClient client(protocol);
	
	//设置发送、接收、连接超时
	socket->setConnTimeout(2000);
	socket->setRecvTimeout(2000);
	socket->setSendTimeout(2000);
	
    printf("before open\n");
	transport->open();
    printf("open ok\n");
	
    printf("before rpc\n");
	//insert your code here  
	Student stu;
	stu.sno = 1;
	stu.sname = "zml";
	stu.ssex = 0;
	stu.sage = 25;
	int ret = client.put(stu);
	printf("client put ret=%d\n", ret);
    printf("rpc ok\n");

    sleep(100);
	
    printf("before close\n");
	transport->close();
    printf("close ok\n");
	return 0;
}
