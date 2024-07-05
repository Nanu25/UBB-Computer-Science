#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


file=$1
word=$2
number=$3

while IFS= read -r line; do
     count=$(grep -o "\<$word\>" <<< "$line" | wc -l)
     if [ "$count" -eq "$number" ]; then
        echo "$line"
     fi
done < "$file"


