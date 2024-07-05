#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


for dir in $@
do
	files=$(find "$dir" -perm 700)
	for f in $files
	do
		if [ -r "$f" ] && [ -w "$f" ]; then
			echo "$f"
		fi
	done

done

