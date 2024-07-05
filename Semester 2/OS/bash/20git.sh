#!/bin/bash

if [ $# -le 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

x=$1
shift

for dir in $@
do
	if [ ! -d "$dir" ]; then
		echo "This directory doesn't exist"
	else
		for file in $(find "$dir" -type f)
		do
			ok=$(grep -c "$x" "$file")
			if grep -q "$x" "$file"; then
				echo "Directory name: $dir"
				echo "File name: $file"
				perm=$(ls -l "$file" | awk '{print $2}')
				echo "Permissions: $perm"
			fi

		done

	fi


done	

