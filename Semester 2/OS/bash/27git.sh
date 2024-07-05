#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid numbers of parameters"
	exit 1
fi


nrfiles=0
nrdir=0
for x in $@
do
	if [ -d $x ]; then
	
		files=$(find $x -type f | awk '{print $0}' | sort -nr | head -1)
		echo "$files"
		((nrdir+=1))
	else 
		if [ -f $x ]; then
			content=$(grep -E '^[A-Z]' $x |sort)
			echo "$content"
			((nrfiles+=1))

		else
			echo "Invalid input"
		fi

	fi

done

echo "$((nrdir/$#))"
echo "$((nrfiles/$#))"

