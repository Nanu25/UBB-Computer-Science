#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

numberfiles=0
for file in $(find $1 -name "*.log") 
do
	((numberfiles+=1))
	sort $file -o $file

	echo $file
done	

echo "The number of files $numberfiles"
