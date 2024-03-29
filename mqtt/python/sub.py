# python3.6

import random

from argparse import ArgumentParser
from paho.mqtt import client as mqtt_client


broker = 'broker.emqx.io'
port = 1883
topic = "python/mqtt"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
# username = 'emqx'
# password = 'public'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
#   client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

    client.subscribe(topic)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    parser = ArgumentParser(description='use MQTT publish a message')
    parser.add_argument('--host', type=str, default='127.0.0.1', help='IP address of broker (default: %(default)s)')
    parser.add_argument('--port', '-p', type=int, default=1883, help='port number of broker (default: %(default)s)')
    args = parser.parse_args()

    print("args: {}".format(args))

    broker = args.host
    port = args.port

    run()

