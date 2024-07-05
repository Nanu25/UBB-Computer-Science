#!/bin/bash

if [ $# -le 0 ]; then 
	echo "Invalid number of parameters"
	exit 1
fi

for x in $@
do
	if [ -f $x ]; then
		echo "File name is $x"
		number_carac=$(wc -c < "$x")
		number_lines=$(wc -l < "$x")
		echo "Number of caracters is $number_carac and the number of lines $number_lines"
	else
	       	if [ -d $x ]; then
			number_files=$(ls -al $x | grep -c "-")
			echo "Directory name is $x"
			echo "The number of files is $number_files"
		else
			echo "Inavlid format"
		fi
	fi	

done

