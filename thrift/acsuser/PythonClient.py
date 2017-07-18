#!/usr/bin/env python  
import sys  
sys.path.append('./gen-py')  
from acsuser import UserService  
from acsuser.ttypes import *  
from thrift import Thrift  
from thrift.transport import TSocket  
from thrift.transport import TTransport  
from thrift.protocol import TCompactProtocol  
  
# Make socket  
transport = TSocket.TSocket('localhost', 9090)  
# Buffering is critical. Raw sockets are very slow  
transport = TTransport.TBufferedTransport(transport)  
# Wrap in a protocol  
protocol = TCompactProtocol.TCompactProtocol(transport)  
# Create a client to use the protocol encoder  
client = UserService.Client(protocol)  
# Connect!  
transport.open()  
# Call Server services    
u = client.get('lll')  
print 'uid=%s uname=%s usex=%d u.uage=%d' %(u.uid,u.uname,u.usex,u.uage)  
  
u1 = User()  
u1.uid='leo'  
u1.uname='yueyue'  
u1.usex=1  
u1.uage=3  
client.add(u1) 
