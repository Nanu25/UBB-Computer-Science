#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

n="$1"
shift

for x in $@
do
	if [ ! -d "$x" ]; then
		echo "This is not a file"
		continue
	fi

	for y in $(find "$x" -type f)
	do
		file_size=$(du -b "$y" | awk '{print $1}')
		if [ "$file_size" -eq 0 ] && [ "$y" = "$n" ]; then
		       		echo "$y"
		fi	       
	done

done

