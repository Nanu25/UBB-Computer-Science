#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid input"
	exit 1
fi

for file in $( find -name '*.txt' ) 
do
	num_lines=$(wc -l < "$file")
	echo $file	

	if [ $num_file -lt 6 ]; then
		cat $file
		echo ""
	else
		head -n 3 $file
		tail -n 3 $file
		echo ""
	fi
done
