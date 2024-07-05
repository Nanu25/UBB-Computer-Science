#More files are given.Display the name of the biggest file.Error messages if we need.

#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


name=""
maxsize=0
maxlines=0
for file in $@
do
	if [ ! -f "$file" ]; then
		echo "This is not a file"
		continue
	fi

	size=$(du -b "$file" | awk '{print $1}')
	if [ $size -ge $maxsize ]; then
		maxsize=$size
		name=$file
	fi

	lines=$(wc -l < "$file")
	if [ $lines -ge $maxlines ]; then
		maxlines=$lines
	fi

done

echo "The file: $name has the max size: $maxsize"
echo "The max lines: $maxlines"

