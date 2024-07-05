#!/bin/bash
A=7
B=9
expr 7 + 9
expr $A + $B

echo $0 $1 $2 $3 $9
echo $*
echo $@
shift 2
echo $#

for A in a b c d e
do
	echo $A
done

for B in $@; do
	echo $B
done 

for B; do
	echo $B
done

for C in *; do
	echo $C
done

