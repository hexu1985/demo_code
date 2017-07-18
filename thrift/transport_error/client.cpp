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

void print_time_now()
{
  time_t now = time(0);
  cerr << "time: " << ctime(&now);
}

void my_pause()
{
  cerr << "pause, entry \\n to continue\n";
  string str;
  getline(cin, str);
}

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

  int max_try_times = 3;
  int origin_timeout = 2000;
  int rate = 2;
  int i;
  print_time_now();
  for (i = 0; i < max_try_times; i++) {
    try {
      socket->setConnTimeout(origin_timeout);
      transport->open();
      break;
    } catch (const TTransportException &e) {
      cerr << "ERROR: type(" << e.getType() << "), errno(" << errno << "), what(" << e.what() << ")\n";
      origin_timeout *= rate;

      my_pause();
      print_time_now();
    }
  }

  if (i == max_try_times) {
      cerr << "connect error\n";
      exit(1);
  }

  socket->setRecvTimeout(10000);
  socket->setSendTimeout(10000);
	
  string str;
  string ret_str;
  while (getline(cin, str)) {
    try {
      client.echo(ret_str, str);
      cerr << ret_str << "\n";
    } catch (const TTransportException &e) {
      cerr << "ERROR: type(" << e.getType() << "), errno(" << errno << "), what(" << e.what() << ")\n";
    }
  }

  transport->close();

  return 0;
}
