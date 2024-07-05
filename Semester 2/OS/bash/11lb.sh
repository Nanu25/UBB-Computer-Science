#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi	


if [ ! -d $1 ]; then
	echo "This is not a directory"
	exit 1
fi

#to find all the files with the given permission
files=$(find "$1" -type f -perm 755)
for file in $files
do
	#to print the initial permissions.
	permissions=$(ls -l "$file" | awk '{print $0}')
	echo "$permissions"
	
	chmod 744 "$file"
	
	permissions=$(ls -l "$file" | awk '{print $0}')
	echo "$permissions"

done

