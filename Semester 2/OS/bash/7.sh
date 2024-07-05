#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid input"
	exit 1
fi


for line in $(cat $1)
do
	echo "The line before the change $line"
	line="$line@scs.ubbcluj.ro"
	echo "Line after the change $line"
done

