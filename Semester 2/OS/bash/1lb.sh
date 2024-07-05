#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid input"
	exit 1
fi

for ((i=1; i<=$1; i++))
do
	sed -n '1,5p' passwd.fake > file_$i
	#rm file_$i
done

