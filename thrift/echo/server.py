#!/usr/bin/env python
import sys

sys.path.append('./gen-py')
from echo import EchoTest
from echo.ttypes import *
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

class EchoTestHandler:
    def echo(self, str):
        return str

port = 9090

if len(sys.argv) == 2:
    port = int(sys.argv[1])

handler = EchoTestHandler()
processor = EchoTest.Processor(handler)
transport = TSocket.TServerSocket('::', port)
transportFactory = TTransport.TBufferedTransportFactory()
protocolFactory = TBinaryProtocol.TBinaryProtocolFactory()

server = TServer.TSimpleServer(processor, transport, transportFactory, protocolFactory)

print("Starting thrift server in python...")
server.serve()
print("done!")

