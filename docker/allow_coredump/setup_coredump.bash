#!/bin/bash

mkdir -p ~/corefile
ulimit -c unlimited
sudo bash -c "echo '1' > /proc/sys/kernel/core_uses_pid"
sudo bash -c "echo '$HOME/corefile/core-%e-%p-%t' > /proc/sys/kernel/core_pattern"
