#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


for file in $@
do
	if [ ! -f "$file" ]; then
		echo "This is not a file"
		continue
	fi

	awk '{fr[$0]++} END{for(line in fr) print fr[line], line}' "$file" | sort -nr | head -n 1

done


