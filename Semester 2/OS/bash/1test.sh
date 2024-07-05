#Write a shell script that counts all the C source programs of the hierarchys of all the directories 
#received as an arguments in the command line.
#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid input"
	exit 0
fi


for directory in $@
do
	if [ -d $directory ]; then
		file=$(find "$directory" -name "*.c") 
		count=0
		for x in $file
		do
			((count+=1))
		done

		echo "Directory $directory has $count c files"

	else
		echo "This is not a directory"
	fi

done

