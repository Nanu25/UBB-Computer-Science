#!/bin/bash

if [ $# -ne 1 ]; then
        echo "Invalid number of arguments"
        exit 1
fi


for x in $(find "$1"  "*.")
do
	len=(${#x})
        if [ $len -le 8 ]; then
                echo $x
                if [ -f $x ]; then
                        head -n 10 "$x"
                fi
        fi

done

