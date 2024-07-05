#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


if [ ! -d $1 ]; then
	echo "This is not a directory"
	exit 1
fi


for file in $(find $1 -name "*.c")
do
	echo "Filename is: $file"

done

lines=0
for file in $(find $1 -type f | grep -E -v "\.c")
do
	nr=$(wc -l < $file)
	lines=$((lines + nr))
done

echo "Total number of lines is $lines"

