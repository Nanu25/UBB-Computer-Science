#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


nr=0
for x in $@
do
	if [ -d $x ]; then
		echo "Permissions for directory $x"
		ls -l $x		
	
	else
		if [ -f $x ]; then
			if [ -r $x ] && [ -w $x ]; then
				sed "s/[0-9]\+/ERROR/g" $x
			fi
		
		else

			awk -v x="$x" -F: '{for(i = 1; i <= NF; i++) if($i == x) print $5}' "passwd.fake"	
		fi

	fi

done


