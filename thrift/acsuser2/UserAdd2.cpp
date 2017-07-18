#include "UserService.h"  
#include <iostream>
#include <string>
#include <thrift/config.h>  
#include <thrift/transport/TSocket.h>  
#include <thrift/transport/TBufferTransports.h>  
#include <thrift/protocol/TCompactProtocol.h>  

using namespace std;
using namespace apache::thrift;  
using namespace apache::thrift::protocol;  
using namespace apache::thrift::transport;  

using boost::shared_ptr;  

int main(int argc, char **argv) try {
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));  
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));  
	boost::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));  

	transport->open();  

	User u;  
	u.uid = "leo";  
	u.uname = "yueyue";  
	u.usex = 1;  
	u.uage = 3;  

	UserServiceClient client(protocol);  
    string str;
    while (getline(cin, str)) {
        cout << "add user: " << str << endl;
        u.uname = str;
	    client.add_v2(u);  
        cout << "add user: " << str << ", ok" << endl;
    }

	transport->close();  
	return 0;  
} catch (const TApplicationException &e) {
    cout << "e: " << e.what() << ", type: " << e.getType() << endl;
}
