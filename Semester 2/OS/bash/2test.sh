#Write a shell script that receives as command line arguments a word (w) followed by 2 numbers (m and n) 
#followed by any number of files. Display the files that contain on the n'th line the word w at least m times.


#!/bin/bash

if [ $# -le 3 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


w=$1
shift
n=$1
shift
m=$1
shift

for file in $@
do
	count=$(awk -v w="$w" -v n="$n" -v m="$m" 'BEGIN{count=0} {for(i = 1; i <= NF; i++) { if(NR == n && $i == w) count++;}} END{if(count >= m) print }' "$file")

	if [[ $count -ge $m ]]; then
		cat $file
	fi

done



