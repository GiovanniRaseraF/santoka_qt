#!/bin/bash

/sbin/ifconfig can0 txqueuelen 1500
sudo /sbin/ifconfig can0 down
sudo /sbin/canconfig can0 bitrate 250000
sudo /sbin/ip link set can0 type can bitrate 250000
sudo /sbin/ifconfig can0 up

export LD_LIBRARY_PATH=/applicat:/applicat/lib

cd;

if [ -f /root/huracanXsantoka ]; then
  /root/huracanXsantoka > /root/test.txt &
fi

