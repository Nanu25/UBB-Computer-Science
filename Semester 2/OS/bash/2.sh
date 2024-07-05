#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

count=0
for file in $(find $1 -name '*.c')
do
	if [ $(wc -l $file | awk '{print $1}') ]; then
		((count+=1))
		echo $file
	fi

	if [ $count -ge 2 ]; then
		break
	fi
done
