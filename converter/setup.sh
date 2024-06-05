#!/bin/bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

sudo ip link set can0 type can bitrate 250000
sudo ip link set up can0