#!/bin/bash

if pip3 --version
then
    echo "pip3 already installed"
else
    sudo apt update
    sudo apt install python3-pip -y
fi

if pip3 show schedule
then
    echo "schedule already installed"
else
    pip3 install schedule
fi

if pip3 show psutil
then
    echo "psutil already installed"
else
    pip3 install psutil
fi
