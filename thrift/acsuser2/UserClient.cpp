#include "UserService.h"  
#include <thrift/config.h>  
#include <thrift/transport/TSocket.h>  
#include <thrift/transport/TBufferTransports.h>  
#include <thrift/protocol/TCompactProtocol.h>  

using namespace apache::thrift;  
using namespace apache::thrift::protocol;  
using namespace apache::thrift::transport;  

using boost::shared_ptr;  

int main(int argc, char **argv) {  
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));  
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));  
	boost::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));  

	transport->open();  

	User u;  
	u.uid = "leo";  
	u.uname = "yueyue";  
	u.usex = 1;  
	u.uage = 3;  
    u.details = "sun";

	UserServiceClient client(protocol);  
	client.add(u);  

	User u1;  
    UserQuery qry;
    qry.uid = "lll";
//    qry.__set_details("xxx");
	client.get(u1,qry);  

	transport->close();  
	printf("uid=%s uname=%s usex=%d uage=%d details=%s\n", u1.uid.c_str(), u1.uname.c_str(), u1.usex, u1.uage, u1.details.c_str());  
	return 0;  
}  
