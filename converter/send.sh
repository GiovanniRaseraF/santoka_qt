#!/bin/bash
# with $1 you need to specify the file
# with $2 the can number 0 or 1 you want to read from the file
# examples:
# ./send.sh file.log 1
# read can1 from file and send it to vcan0

canplayer -I $1 vcan0=can$2
