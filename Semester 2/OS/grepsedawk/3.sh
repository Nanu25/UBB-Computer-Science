#!/bin/bash

echo($1)

for A in $@; do
	echo $A
	if [ $(($4 % 7)) -eq 0 ]; then
		echo($6)
	fi
done
