from argparse import ArgumentParser
from datetime import datetime
import time
import os
import paho.mqtt.client as mqtt

receive_msg = False

def subscribe(broker="127.0.0.1", port=1883):
    def on_message(client, userdata, message):
        time.sleep(1)
        global receive_msg
        receive_msg = True
        print("received message =",str(message.payload.decode("utf-8")))

    print("creating new instance")
    client = mqtt.Client("subscriber.{}".format(os.getpid())) #create new instance
    client.on_message = on_message
    print("connecting to broker")
    client.connect(broker,port) #connect to broker
    client.loop_start() #start loop to process received messages
    print("subscribing ")
    topic = "hello-mqtt"
    client.subscribe(topic)
    global receive_msg
    while True:
        if receive_msg == True:
            break
        time.sleep(2)
    client.disconnect() #disconnect
    client.loop_stop() #stop loop


if __name__ == "__main__":
    parser = ArgumentParser(description='use MQTT publish a message')
    parser.add_argument('--host', type=str, default='127.0.0.1', help='IP address of broker (default: %(default)s)')
    parser.add_argument('--port', '-p', type=int, default=1883, help='port number of broker (default: %(default)s)')
    args = parser.parse_args()

    print("args: {}".format(args))

    subscribe(args.host, args.port)

