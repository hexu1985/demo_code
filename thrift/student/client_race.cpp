#include "Serv.h"  // 替换成你的.h  
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

ServClient *client = nullptr;

void call_rpc(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck);

	//insert your code here  
    std::cout << "thread " << id << "\n";
	Student stu;
	stu.sno = id;
	stu.sname = "zml";
	stu.ssex = 0;
	stu.sage = 25;
	int ret = client->put(stu);
    std::cout << "thread " << id << "put ok\n";

}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

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
    std::thread threads[10];
    for (int i = 0; i < 10; i++) {
        threads[i] = std::thread(call_rpc, i);
    }

    std::cout << "10 threads ready to race...\n";
    go();

    for (auto& th : threads) th.join();
	
    printf("before close\n");
	transport->close();
    printf("close ok\n");
	return 0;
}
