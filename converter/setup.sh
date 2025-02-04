#!/bin/bash
sudo ip link set down vcan0
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan || 
sudo ip link set up vcan0

# sudo ip link set down can0
# sudo ip link set can0 type can bitrate 250000
# sudo ip link set up can0