#!/usr/bin/env python3
# encoding: utf-8

import time

from cyber_py import cyber
from cyber.examples.proto import examples_pb2

def message_callback(msg):
    print("Received message seq->", msg.seq)
    print("msgcontent->", msg.content)

if __name__ == "__main__":
    print("hello talker.py")
    cyber.init()
    node = cyber.Node("talker_py")
    talker = node.create_writer("channel/chatter",
                examples_pb2.Chatter)

    msg = examples_pb2.Chatter()
    seq = 0
    while not cyber.is_shutdown():
        msg.timestamp = int(time.time() * (10**9))
        msg.lidar_timestamp = int(time.time() * (10**9))
        msg.seq = seq
        msg.content = b"Hello, apollo!"
        talker.write(msg)
        seq += 1
        time.sleep(1.0)
