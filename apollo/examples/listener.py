#!/usr/bin/env python3
# encoding: utf-8

import time

from cyber_py import cyber
from cyber.examples.proto import examples_pb2

def message_callback(msg):
    print("Received message seq->", msg.seq)
    print("msgcontent->", msg.content)

if __name__ == "__main__":
    print("hello listener.py")
    cyber.init()
    node = cyber.Node("listener_py")
    node.create_reader("channel/chatter",
                examples_pb2.Chatter,
                message_callback)

    while not cyber.is_shutdown():
        time.sleep(0.5)
