#!/bin/bash

if pip3 --version
then
    echo "pip3 already installed"
else
    sudo apt update
    sudo apt install python3-pip -y
fi

if python3 -c 'import schedule'
then
    echo "schedule already installed"
else
    pip3 install schedule
fi

if python3 -c 'import psutil'
then
    echo "psutil already installed"
else
    pip3 install psutil
fi

if python3 -c 'import matplotlib'
then
    echo "matplotlib already installed"
else
    pip3 install matplotlib
fi

#if python -c 'import Tkinter'
#then
#    echo "Tkinter already installed"
#else
#    sudo apt update
#    sudo apt install python-tk -y
#fi
