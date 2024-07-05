#Write a shell script that receives a number n followed by any number of files as command line arguments. 
#The script will display all the words from each file with the frequency greater the n.

#!/bin/bash

if [ $# -le 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

n=$1
shift 
for file in $@
do
	if [ ! -f $file ]; then
		echo "This is not a file"
		exit 1
	fi
	
	words=$(awk -v n="$n" '{for(i = 1; i <= NF; i++) fr[$i]++} END{for (word in fr) if(fr[word] > n) print word}' "$file") 
	echo "The words are: $words"

done	


