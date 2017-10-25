#!/bin/bash

print_usage() {
    echo "usage:"
    echo "    start.sh host port"
    echo "    start.sh port"
    echo "    start.sh"
}

listen_host="0.0.0.0"
listen_port=5000

if (( $# == 1 ))
then
    if [[ $1 =~ "-h" || $1 =~ "--help" ]]
    then
        print_usage
        exit
    fi
    listen_port=$1
fi

if (( $# == 2 ))
then
    listen_host=$1
    listen_port=$2
fi

python app/main.py runserver --host $listen_host --port $listen_port 
