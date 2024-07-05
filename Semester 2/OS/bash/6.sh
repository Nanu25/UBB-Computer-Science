#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid input"
	exit 1
fi


files=$(find "$1" -perm o+w)
for file in $files
do

	echo "$file"
	chmod o-w "$file"
	echo "$file"
done	

