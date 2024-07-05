#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid input"
	exit 1
fi

read word

apparence=0
for file in $@
do
	if [ -f $file ]; then
		((apparence+=$(grep -Ec $word "$file")))
	else
		echo "$file this is not a file"
	fi
done

echo "The number of apparence $apparence"



