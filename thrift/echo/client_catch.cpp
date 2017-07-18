/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <iostream>
#include <string>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "EchoTest.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace demo;

int main(int argc, char** argv) {
  string host = "localhost";
  int port = 9090;

  if (argc == 2) {
    int tmp = atoi(argv[1]);
    if (tmp != 0) port = tmp;
  } else if (argc == 3) {
    host = argv[1];
    int tmp = atoi(argv[2]);
    if (tmp != 0) port = tmp;
  }

  boost::shared_ptr<TSocket> socket(new TSocket(host, port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  EchoTestClient client(protocol);

  try {
    transport->open();

    string str;
    string ret_str;
    while (getline(cin, str)) {
      client.echo(ret_str, str);
      cerr << ret_str << "\n";
    }

    transport->close();
  } catch (TException &tx) {
    cerr << "ERROR: " << tx.what() << "\n";
  }

  return 0;
}
