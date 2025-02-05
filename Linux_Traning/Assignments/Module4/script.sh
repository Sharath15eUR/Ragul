#!/bin/bash

if [ ! -f "$1" ]; then
   echo "File is not present"
fi 

grep -E '"frame.time"|"wlan.fc.type"|"wlan.fc.subtype"' "$1" > output.txt



