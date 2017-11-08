#!/usr/bin/env python
import sys

sys.path.append('./gen-py')
from echo import EchoTest
from echo.ttypes import *
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

host = 'localhost'
port = 9090

if len(sys.argv) == 2:
    port = int(sys.argv[1])

if len(sys.argv) == 3:
    host = sys.argv[1]
    port = int(sys.argv[2])

# Make socket  
transport = TSocket.TSocket(host, port)
# Buffering is critical. Raw sockets are very slow  
transport = TTransport.TBufferedTransport(transport)
# Wrap in a protocol  
protocol = TBinaryProtocol.TBinaryProtocol(transport)
# Create a client to use the protocol encoder  
client = EchoTest.Client(protocol)
# Connect!  
transport.open()

# Call Server services    
ret = client.echo('hello')
print("%s" % ret)

while 1:
    data = sys.stdin.readline()
    if not len(data):
        break
    ret = client.echo(data)
    print("%s" % ret)
