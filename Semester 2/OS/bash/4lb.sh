#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

for file in $(find -name "*.txt")
do
	if grep -q "[0-9]\{5,\}" $file; then
		echo "File name is $file"
	
	fi
	
done

