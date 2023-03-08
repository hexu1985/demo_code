from argparse import ArgumentParser
from datetime import datetime
import os
import time
import paho.mqtt.client as mqtt

def publish(broker="127.0.0.1", port=1883):
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    def on_publish(client,userdata,result):             #create function for callback
        print("{}: data published: {}, {}, {} \n".format(
            datetime.now(), client, userdata, result))

    def on_disconnect(client, userdata, result):
        print("{}: on disconnect: {}, {}, {} \n".format(
            datetime.now(), client, userdata, result))

    client1= mqtt.Client("publisher.{}".format(os.getpid()))                           #create client object
    client1.on_connect = on_connect
    client1.on_publish = on_publish                          #assign function to callback
    client1.on_disconnect = on_disconnect
    client1.connect(broker,port)                                 #establish connection
    topic = "hello-mqtt"

    while True:
        message = "The time is {}".format(datetime.now())
        ret= client1.publish(topic, message)                   #publish
        if ret[0] != 0:
            print("Failed to send message")
        time.sleep(120)

if __name__ == "__main__":
    parser = ArgumentParser(description='use MQTT publish a message')
    parser.add_argument('--host', type=str, default='127.0.0.1', help='IP address of broker (default: %(default)s)')
    parser.add_argument('--port', '-p', type=int, default=1883, help='port number of broker (default: %(default)s)')
    args = parser.parse_args()

    print("args: {}".format(args))

    publish(args.host, args.port)

