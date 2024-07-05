#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


read n
read file
while [ $n -ne 0 ]; do
	words=$(head  -n $n "$1")
	touch $file
	echo $words>>$file
	cat "$file"

	read n
done

carac=$(wc -c "$file")
echo "Number of caracters $carac"

lines=$(wc -l "$file")
echo "Number of lines $lines"

words=$(wc -w "$file")
echo "Number of words $words"



