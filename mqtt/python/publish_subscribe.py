from argparse import ArgumentParser
import time
import os
import paho.mqtt.client as mqtt

def mqtt_test(broker="127.0.0.1", port=1883):
    #broker="broker.hivemq.com"
    #define callback
    def on_message(client, userdata, message):
        time.sleep(1)
        print("received message =",str(message.payload.decode("utf-8")))
    
    client= mqtt.Client("client.{}".format(os.getpid())) #create client object client1.on_publish = on_publish #assign function to callback client1.connect(broker,port) #establish connection client1.publish("house/bulb1","on")
    ######Bind function to callback
    client.on_message=on_message
    #####
    print("connecting to broker ",broker)
    client.connect(broker,port)#connect
    client.loop_start() #start loop to process received messages
    print("subscribing ")
    client.subscribe("house/bulb1")#subscribe
    time.sleep(2)
    print("publishing ")
    client.publish("house/bulb1","on")#publish
    time.sleep(4)
    client.disconnect() #disconnect
    client.loop_stop() #stop loop


if __name__ == "__main__":
    parser = ArgumentParser(description='use MQTT publish a message')
    parser.add_argument('--host', type=str, default='127.0.0.1', help='IP address of broker (default: %(default)s)')
    parser.add_argument('--port', '-p', type=int, default=1883, help='port number of broker (default: %(default)s)')
    args = parser.parse_args()

    print("args: {}".format(args))

    mqtt_test(args.host, args.port)

