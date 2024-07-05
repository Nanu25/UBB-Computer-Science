#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid input"
fi


for directory in $@
do
	if [ ! -d "$directory" ]; then
		echo "This is not a directory"
	else
		nr_dir=0
		nr_exec=0
		nr_neex=0
		for file in $(find "$directory" -type f)
		do
			if [ -f "$file" ]; then
				((nr_dir+=1))
				if [ -x "$file" ]; then
					((nr_exec+=1))
				else
					((nr_neex+=1))
				fi
			fi
			
		done

		echo "Directory name $directory"
		echo "Number of directories $nr_dir"
		echo "Number of executables $nr_exec"
		echo "Number of neexecutables $nr_neex"

	fi

done


