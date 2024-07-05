#Write a shell script that receive a list of arguments in command line. For all arguments that are directories the
#script display the fullname of its owner followed by the path and the size of the smallest file in its hierarchy.
#For all arguments that are files in the current directory the script will display the file with its lines in reverse
#order. All input data must be validated. Afisati mesaje de eroare.


#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid input"
	exit 1
fi


for x in $@
do
	if [ -d "$x" ]; then
		owner=$(ls -ld "$x" | awk '{print $3}')
		echo "Owner is $owner"
		path=$(pwd "$x") 
		echo "Path is $path"
		min_file=$(find "$x" -type f | ls -l | awk '{print $7}' | sort -n | head -n 2)
		echo "The minim file is $min_file"
		
	else
		if [ -f "$x" ]; then
			lines=$(awk '{a[NR] = $0} END {for(i = NR; i >= 1; i--) print a[i]}' "$x")
			echo "$lines"
		else
			echo "Invalid argument"
		fi

	fi
done



