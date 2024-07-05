#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid input!"
	exit 1
fi


number_files=0
number_lines=0
for file in $(find -name "*.txt")
do
	((number_files+=1))
	aux=$(wc -l $file)
	 ((number_lines+=$(echo "$aux" | cut -d ' ' -f 1)))
done


echo "The avrage is $((number_lines / number_files))"


