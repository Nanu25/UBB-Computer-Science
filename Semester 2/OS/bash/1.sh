#!/bin/bash

for user in $(cat who.fake | awk '{print $1}')
do
	process=$(grep -Ec "^${user}" ps.fake)
	echo "$user $process"
	
done
