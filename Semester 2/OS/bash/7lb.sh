#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

read word1
read word2

for file in $@
do
	if [ -f $file ]; then
		sed "s/$word1/$word2/g" "$file"
		cat $file	
	else
		echo "$file is not a file"
	fi

done 
