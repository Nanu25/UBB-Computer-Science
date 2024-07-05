#!/bin/bash


if [ $# -ne 3 ]; then
	echo "invalid number of paramaters"
	exit 1
fi


directory=$1
owner=$2
size=$3
shift 3

for file in $(find "$directory" -type f)
do
	ow=$(ls -l "$file" | awk '{print $3}')   #owner of the file
	sz=$(ls -l "$file" | awk '{print $5}')   #size of the file
	if [  $size -ge $sz ] && [ $owner == $ow ] ; then
		echo "$ow $sz"

		words=$(cat $file | grep -E "^[aeiouAEIOU]" |  sort | uniq -c | head -10)
		echo "$words"
	fi
done

